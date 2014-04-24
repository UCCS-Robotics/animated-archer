#include <i2c_t3.h>

// Firmware version.
// 0xMMmmRRRR
// MM - Major
// mm - Minor
// RRRR - Revision
const uint32_t FIRMWARE_VER = 0x01010001;

// RawHID packets are always 64 bytes.
const int PACKET_SIZE = 64;

// Time (in milliseconds) to wait for a packet to send before giving up.
const int SEND_TIMEOUT = 100;

// Time (in milliseconds) between info packets.
const unsigned int INFO_PACKET_DELAY = 1000; // 1 sec.

typedef enum _PacketType
{
  // These are sent from the PC to the device.
  PacketType_ReqRead = 'R',  // Request a read from an I2C slave.
  PacketType_ReqWrite = 'W', // Request a write to an I2C slave.
  
  // These are send from the device to the PC.
  PacketType_Info = 'I',     // Device is idle but responding/working.
  PacketType_Data = 'D',     // Data returned from a I2C slave read request.
  PacketType_Status = 'S',   // Status (return code) of a request.
} PacketType;

typedef struct _Packet
{
  uint8_t  type;      // 00 Packet type.
  uint8_t  addr;      // 01 Address for the I2C slave.
  uint8_t  sz;        // 02 Size (in bytes) of the transaction.
  uint8_t  reserved1; // 03 Reserved byte (should be 0).
  uint32_t tag;       // 04 Data from PC that will be echoed back (or 0).
  uint32_t reserved2; // 08 Reserved bytes (should be 0).
  uint8_t  data[48];  // 0C Data for the command.
  uint32_t crc;       // 3C CRC-32 checksum of the packet (bytes 00-3B).
} __attribute__ ((__packed__)) Packet;

// Function prototypes.
void sendInfoPacket();
void parseReqRead(Packet *p);
void parseReqWrite(Packet *p);
uint32_t crc32(const void *data, uint32_t sz);

void setup()
{
  // Initialize the I2C module.
  Wire.begin();
}

// Time until the next info packet should send.
elapsedMillis msUntilNextInfoPacket;

void sendInfoPacket()
{
  // Buffer for the info packet.
  byte buffer[PACKET_SIZE];

  // Cast the buffer to a packet.
  Packet *p = (Packet*)buffer;
  
  // Set the packet data.
  p->type = PacketType_Info;
  p->addr = 0;
  p->sz = 0;
  p->reserved1 = 0;
  p->tag = FIRMWARE_VER;
  p->reserved2 = 0;

  // Zero the data.
  for(uint8_t i = 0; i < 48; i++)
    p->data[i] = 0;
    
  // Calculate the CRC-32 checksum.
  p->crc = crc32(buffer, PACKET_SIZE - 4);
  
  // Transmit the packet and hope to hell it goes through.
  RawHID.send(buffer, SEND_TIMEOUT);
}

void parseReqRead(Packet *p)
{
  // Read data from the I2C slave.
  Wire.requestFrom(p->addr, (size_t)p->sz);

  // Get how much data was read.
  int avail = Wire.available();
  
  // Sanity check the number of bytes.
  if(avail > 48)
    avail = 48;

  // Create the data packet.
  p->type = PacketType_Data;
  p->sz = avail;
  p->reserved1 = 0;
  p->reserved2 = 0;

  // Read the data.
  for(uint8_t i = 0; i < avail; i++)
    p->data[i] = Wire.receive();

  // Zero the excess data.
  for(uint8_t i = avail; i < 48; i++)
    p->data[i] = 0;
    
  // Calculate the CRC-32 checksum.
  p->crc = crc32(p, PACKET_SIZE - 4);
  
  // Transmit the packet and hope to hell it goes through.
  RawHID.send(p, SEND_TIMEOUT);
}

void parseReqWrite(Packet *p)
{
  // Start an I2C slave write.
  Wire.beginTransmission(p->addr);

  // Write the data to the I2C slave.  
  for(int i = 0; i < p->sz; i++)
    Wire.send(p->data[i]);

  // Create the status (return code) packet.
  p->type = PacketType_Status;
  p->reserved1 = 0;
  p->reserved2 = 0;
  
  // Set the return code by completing the transaction.
  // 0=success, 1=data too long, 2=recv addr NACK,
  // 3=recv data NACK, 4=other error
  p->data[0] = Wire.endTransmission();

  // Zero the data.
  for(uint8_t i = 1; i < 48; i++)
    p->data[i] = 0;
    
  // Calculate the CRC-32 checksum.
  p->crc = crc32(p, PACKET_SIZE - 4);
  
  // Transmit the packet and hope to hell it goes through.
  RawHID.send(p, SEND_TIMEOUT);
}

void loop()
{ 
  // If it has been long enough, send another info packet.
  if(msUntilNextInfoPacket >= INFO_PACKET_DELAY)
  {
    msUntilNextInfoPacket -= INFO_PACKET_DELAY;
    sendInfoPacket();
  }

  // Where to store the current packet.
  byte buffer[PACKET_SIZE];

  // Don't wait (no timeout) and ignore any fails to read a full packet.
  if(RawHID.recv(buffer, 0) != PACKET_SIZE)
    return;
  
  // Cast the buffer to a packet.
  Packet *p = (Packet*)buffer;

  // Calculate the CRC-32 checksum of the packet.
  uint32_t crc = crc32(buffer, PACKET_SIZE - 4);
  
  // Validate the CRC-32 checksum. If it's invalid, ignore the packet.
  if(p->crc != crc)
    return;
    
  // Sanity check the size.
  if(p->sz > 48)
    return;

  // Process the packet based on it's type.
  // Ignore all unknown or unhandled packet types.
  switch(p->type)
  {
    case PacketType_ReqRead:
      parseReqRead(p);
      break;
    case PacketType_ReqWrite:
      parseReqWrite(p);
      break;
    default:
      break;
  }
}

// Undefine the Arduino CRC shit.
#undef CRC_CRC
#undef CRC_GPOLY
#undef CRC_CTRL

/* ----------------------------------------------------------------------------
   -- CRC
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CRC_Peripheral CRC
 * @{
 */

/** CRC - Peripheral register structure */
typedef struct CRC_MemMap {
  union {                                          /* offset: 0x0 */
    uint32_t CRC;                                    /**< CRC Data Register, offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      uint16_t CRCL;                                   /**< CRC_CRCL register., offset: 0x0 */
      uint16_t CRCH;                                   /**< CRC_CRCH register., offset: 0x2 */
    } ACCESS16BIT;
    struct {                                         /* offset: 0x0 */
      uint8_t CRCLL;                                   /**< CRC_CRCLL register., offset: 0x0 */
      uint8_t CRCLU;                                   /**< CRC_CRCLU register., offset: 0x1 */
      uint8_t CRCHL;                                   /**< CRC_CRCHL register., offset: 0x2 */
      uint8_t CRCHU;                                   /**< CRC_CRCHU register., offset: 0x3 */
    } ACCESS8BIT;
  };
  union {                                          /* offset: 0x4 */
    uint32_t GPOLY;                                  /**< CRC Polynomial Register, offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint16_t GPOLYL;                                 /**< CRC_GPOLYL register., offset: 0x4 */
      uint16_t GPOLYH;                                 /**< CRC_GPOLYH register., offset: 0x6 */
    } GPOLY_ACCESS16BIT;
    struct {                                         /* offset: 0x4 */
      uint8_t GPOLYLL;                                 /**< CRC_GPOLYLL register., offset: 0x4 */
      uint8_t GPOLYLU;                                 /**< CRC_GPOLYLU register., offset: 0x5 */
      uint8_t GPOLYHL;                                 /**< CRC_GPOLYHL register., offset: 0x6 */
      uint8_t GPOLYHU;                                 /**< CRC_GPOLYHU register., offset: 0x7 */
    } GPOLY_ACCESS8BIT;
  };
  union {                                          /* offset: 0x8 */
    uint32_t CTRL;                                   /**< CRC Control Register, offset: 0x8 */
    struct {                                         /* offset: 0x8 */
      uint8_t RESERVED_0[3];
      uint8_t CTRLHU;                                  /**< CRC_CTRLHU register., offset: 0xB */
    } CTRL_ACCESS8BIT;
  };
} volatile *CRC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register accessors */
#define CRC_CRC_REG(base)                        ((base)->CRC)
#define CRC_CRCL_REG(base)                       ((base)->ACCESS16BIT.CRCL)
#define CRC_CRCH_REG(base)                       ((base)->ACCESS16BIT.CRCH)
#define CRC_CRCLL_REG(base)                      ((base)->ACCESS8BIT.CRCLL)
#define CRC_CRCLU_REG(base)                      ((base)->ACCESS8BIT.CRCLU)
#define CRC_CRCHL_REG(base)                      ((base)->ACCESS8BIT.CRCHL)
#define CRC_CRCHU_REG(base)                      ((base)->ACCESS8BIT.CRCHU)
#define CRC_GPOLY_REG(base)                      ((base)->GPOLY)
#define CRC_GPOLYL_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYL)
#define CRC_GPOLYH_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYH)
#define CRC_GPOLYLL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLL)
#define CRC_GPOLYLU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLU)
#define CRC_GPOLYHL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHL)
#define CRC_GPOLYHU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHU)
#define CRC_CTRL_REG(base)                       ((base)->CTRL)
#define CRC_CTRLHU_REG(base)                     ((base)->CTRL_ACCESS8BIT.CTRLHU)

/**
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/* CRC Bit Fields */
#define CRC_CRC_LL_MASK                          0xFFu
#define CRC_CRC_LL_SHIFT                         0
#define CRC_CRC_LL(x)                            (((uint32_t)(((uint32_t)(x))<<CRC_CRC_LL_SHIFT))&CRC_CRC_LL_MASK)
#define CRC_CRC_LU_MASK                          0xFF00u
#define CRC_CRC_LU_SHIFT                         8
#define CRC_CRC_LU(x)                            (((uint32_t)(((uint32_t)(x))<<CRC_CRC_LU_SHIFT))&CRC_CRC_LU_MASK)
#define CRC_CRC_HL_MASK                          0xFF0000u
#define CRC_CRC_HL_SHIFT                         16
#define CRC_CRC_HL(x)                            (((uint32_t)(((uint32_t)(x))<<CRC_CRC_HL_SHIFT))&CRC_CRC_HL_MASK)
#define CRC_CRC_HU_MASK                          0xFF000000u
#define CRC_CRC_HU_SHIFT                         24
#define CRC_CRC_HU(x)                            (((uint32_t)(((uint32_t)(x))<<CRC_CRC_HU_SHIFT))&CRC_CRC_HU_MASK)
/* CRCL Bit Fields */
#define CRC_CRCL_CRCL_MASK                       0xFFFFu
#define CRC_CRCL_CRCL_SHIFT                      0
#define CRC_CRCL_CRCL(x)                         (((uint16_t)(((uint16_t)(x))<<CRC_CRCL_CRCL_SHIFT))&CRC_CRCL_CRCL_MASK)
/* CRCH Bit Fields */
#define CRC_CRCH_CRCH_MASK                       0xFFFFu
#define CRC_CRCH_CRCH_SHIFT                      0
#define CRC_CRCH_CRCH(x)                         (((uint16_t)(((uint16_t)(x))<<CRC_CRCH_CRCH_SHIFT))&CRC_CRCH_CRCH_MASK)
/* CRCLL Bit Fields */
#define CRC_CRCLL_CRCLL_MASK                     0xFFu
#define CRC_CRCLL_CRCLL_SHIFT                    0
#define CRC_CRCLL_CRCLL(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CRCLL_CRCLL_SHIFT))&CRC_CRCLL_CRCLL_MASK)
/* CRCLU Bit Fields */
#define CRC_CRCLU_CRCLU_MASK                     0xFFu
#define CRC_CRCLU_CRCLU_SHIFT                    0
#define CRC_CRCLU_CRCLU(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CRCLU_CRCLU_SHIFT))&CRC_CRCLU_CRCLU_MASK)
/* CRCHL Bit Fields */
#define CRC_CRCHL_CRCHL_MASK                     0xFFu
#define CRC_CRCHL_CRCHL_SHIFT                    0
#define CRC_CRCHL_CRCHL(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CRCHL_CRCHL_SHIFT))&CRC_CRCHL_CRCHL_MASK)
/* CRCHU Bit Fields */
#define CRC_CRCHU_CRCHU_MASK                     0xFFu
#define CRC_CRCHU_CRCHU_SHIFT                    0
#define CRC_CRCHU_CRCHU(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CRCHU_CRCHU_SHIFT))&CRC_CRCHU_CRCHU_MASK)
/* GPOLY Bit Fields */
#define CRC_GPOLY_LOW_MASK                       0xFFFFu
#define CRC_GPOLY_LOW_SHIFT                      0
#define CRC_GPOLY_LOW(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_GPOLY_LOW_SHIFT))&CRC_GPOLY_LOW_MASK)
#define CRC_GPOLY_HIGH_MASK                      0xFFFF0000u
#define CRC_GPOLY_HIGH_SHIFT                     16
#define CRC_GPOLY_HIGH(x)                        (((uint32_t)(((uint32_t)(x))<<CRC_GPOLY_HIGH_SHIFT))&CRC_GPOLY_HIGH_MASK)
/* GPOLYL Bit Fields */
#define CRC_GPOLYL_GPOLYL_MASK                   0xFFFFu
#define CRC_GPOLYL_GPOLYL_SHIFT                  0
#define CRC_GPOLYL_GPOLYL(x)                     (((uint16_t)(((uint16_t)(x))<<CRC_GPOLYL_GPOLYL_SHIFT))&CRC_GPOLYL_GPOLYL_MASK)
/* GPOLYH Bit Fields */
#define CRC_GPOLYH_GPOLYH_MASK                   0xFFFFu
#define CRC_GPOLYH_GPOLYH_SHIFT                  0
#define CRC_GPOLYH_GPOLYH(x)                     (((uint16_t)(((uint16_t)(x))<<CRC_GPOLYH_GPOLYH_SHIFT))&CRC_GPOLYH_GPOLYH_MASK)
/* GPOLYLL Bit Fields */
#define CRC_GPOLYLL_GPOLYLL_MASK                 0xFFu
#define CRC_GPOLYLL_GPOLYLL_SHIFT                0
#define CRC_GPOLYLL_GPOLYLL(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYLL_GPOLYLL_SHIFT))&CRC_GPOLYLL_GPOLYLL_MASK)
/* GPOLYLU Bit Fields */
#define CRC_GPOLYLU_GPOLYLU_MASK                 0xFFu
#define CRC_GPOLYLU_GPOLYLU_SHIFT                0
#define CRC_GPOLYLU_GPOLYLU(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYLU_GPOLYLU_SHIFT))&CRC_GPOLYLU_GPOLYLU_MASK)
/* GPOLYHL Bit Fields */
#define CRC_GPOLYHL_GPOLYHL_MASK                 0xFFu
#define CRC_GPOLYHL_GPOLYHL_SHIFT                0
#define CRC_GPOLYHL_GPOLYHL(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYHL_GPOLYHL_SHIFT))&CRC_GPOLYHL_GPOLYHL_MASK)
/* GPOLYHU Bit Fields */
#define CRC_GPOLYHU_GPOLYHU_MASK                 0xFFu
#define CRC_GPOLYHU_GPOLYHU_SHIFT                0
#define CRC_GPOLYHU_GPOLYHU(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYHU_GPOLYHU_SHIFT))&CRC_GPOLYHU_GPOLYHU_MASK)
/* CTRL Bit Fields */
#define CRC_CTRL_TCRC_MASK                       0x1000000u
#define CRC_CTRL_TCRC_SHIFT                      24
#define CRC_CTRL_WAS_MASK                        0x2000000u
#define CRC_CTRL_WAS_SHIFT                       25
#define CRC_CTRL_FXOR_MASK                       0x4000000u
#define CRC_CTRL_FXOR_SHIFT                      26
#define CRC_CTRL_TOTR_MASK                       0x30000000u
#define CRC_CTRL_TOTR_SHIFT                      28
#define CRC_CTRL_TOTR(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TOTR_SHIFT))&CRC_CTRL_TOTR_MASK)
#define CRC_CTRL_TOT_MASK                        0xC0000000u
#define CRC_CTRL_TOT_SHIFT                       30
#define CRC_CTRL_TOT(x)                          (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TOT_SHIFT))&CRC_CTRL_TOT_MASK)
/* CTRLHU Bit Fields */
#define CRC_CTRLHU_TCRC_MASK                     0x1u
#define CRC_CTRLHU_TCRC_SHIFT                    0
#define CRC_CTRLHU_WAS_MASK                      0x2u
#define CRC_CTRLHU_WAS_SHIFT                     1
#define CRC_CTRLHU_FXOR_MASK                     0x4u
#define CRC_CTRLHU_FXOR_SHIFT                    2
#define CRC_CTRLHU_TOTR_MASK                     0x30u
#define CRC_CTRLHU_TOTR_SHIFT                    4
#define CRC_CTRLHU_TOTR(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TOTR_SHIFT))&CRC_CTRLHU_TOTR_MASK)
#define CRC_CTRLHU_TOT_MASK                      0xC0u
#define CRC_CTRLHU_TOT_SHIFT                     6
#define CRC_CTRLHU_TOT(x)                        (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TOT_SHIFT))&CRC_CTRLHU_TOT_MASK)

/**
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base pointer */
#define CRC_BASE_PTR                             ((CRC_MemMapPtr)0x40032000u)

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register instance definitions */
/* CRC */
#define CRC_CRC                                  CRC_CRC_REG(CRC_BASE_PTR)
#define CRC_GPOLY                                CRC_GPOLY_REG(CRC_BASE_PTR)
#define CRC_CTRL                                 CRC_CTRL_REG(CRC_BASE_PTR)
#define CRC_CRCL                                 CRC_CRCL_REG(CRC_BASE_PTR)
#define CRC_CRCH                                 CRC_CRCH_REG(CRC_BASE_PTR)
#define CRC_CRCLL                                CRC_CRCLL_REG(CRC_BASE_PTR)
#define CRC_CRCLU                                CRC_CRCLU_REG(CRC_BASE_PTR)
#define CRC_CRCHL                                CRC_CRCHL_REG(CRC_BASE_PTR)
#define CRC_CRCHU                                CRC_CRCHU_REG(CRC_BASE_PTR)
#define CRC_GPOLYL                               CRC_GPOLYL_REG(CRC_BASE_PTR)
#define CRC_GPOLYH                               CRC_GPOLYH_REG(CRC_BASE_PTR)
#define CRC_GPOLYLL                              CRC_GPOLYLL_REG(CRC_BASE_PTR)
#define CRC_GPOLYLU                              CRC_GPOLYLU_REG(CRC_BASE_PTR)
#define CRC_GPOLYHL                              CRC_GPOLYHL_REG(CRC_BASE_PTR)
#define CRC_GPOLYHU                              CRC_GPOLYHU_REG(CRC_BASE_PTR)
#define CRC_CTRLHU                               CRC_CTRLHU_REG(CRC_BASE_PTR)

/**
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/**
 * @}
 */ /* end of group CRC_Peripheral */

uint32_t crc32(const void *data, uint32_t sz)
{
  // Use a 32-bit pointer.
  const uint32_t *data32 = (const uint32_t*)data;

  // Divide by 4.
  sz >>=2;

  // 32-bit mode, transpose read/write bytes/bits, complement read.
  CRC_CTRL = CRC_CTRL_TCRC_MASK | CRC_CTRL_FXOR_MASK |
    CRC_CTRL_TOT(2)  | CRC_CTRL_TOTR(2);

  // Set the polynomial.
  CRC_GPOLY = 0x04C11DB7;

  // Write the seed value.
  CRC_CTRL |= CRC_CTRL_WAS_MASK;
  CRC_CRC = 0xFFFFFFFF;

  // Prepare to write the data.
  CRC_CTRL &= ~CRC_CTRL_WAS_MASK;

  // Write the data.
  while(sz--)
    CRC_CRC = *(data32++);

  return CRC_CRC;
}

