#ifndef BURSTPROGRAM_H
#define BURSTPROGRAM_H

#include <stdint.h>

#include <QByteArray>
#include <QSharedPointer>
#include <QSharedDataPointer>

class BurstProgramData;

class BurstProgram
{
public:
    BurstProgram();

    bool isValid() const;

    // Maximum number of burst programs.
    static const int MAX_PROG = 4;

    // Invalid program ID.
    static const uint8_t INVALID_PROG = 0xFF;

    void addRead(uint8_t addr, uint8_t sz);
    void addWrite(uint8_t addr, const QByteArray& data, bool stop = true);
    void addWrite(uint8_t addr, const uint8_t *data, uint8_t sz, bool stop = true);

    uint8_t programID() const;
    void setProgramID(uint8_t id);

    uint16_t runInterval() const;
    void setRunInterval(uint16_t ms);

    QByteArray data() const;

    typedef enum _BurstOpcode
    {
      BurstOpcode_NOP = 0,
      BurstOpcode_Read = 1,
      BurstOpcode_Write = 2,
      BurstOpcode_WriteNoStop = 3
    } BurstOpcode;

    typedef struct _ProgramData
    {
      uint16_t runInterval; // 00 - Time (in ms) to wait for the program to execute again.
      uint8_t  programID;   // 02 - ID of the program (or 0xFF for an invalid program).
      uint8_t  program[45]; // 03 - Data for the program consisting of an opcode, address, size.
    } __attribute__ ((__packed__)) ProgramData;

private:
    QSharedDataPointer<BurstProgramData> d;
};

class BurstProgramData : public QSharedData
{
public:
    BurstProgramData();

    int size;
    bool valid;
    BurstProgram::ProgramData prog;
};

typedef QSharedPointer<BurstProgram> BurstProgramPtr;

Q_DECLARE_METATYPE(BurstProgram);
Q_DECLARE_METATYPE(BurstProgramPtr);

#endif // BURSTPROGRAM_H
