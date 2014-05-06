#include "burstprogram.h"

BurstProgramData::BurstProgramData() : size(0), valid(true)
{
    // Initialize the data.
    prog.programID = BurstProgram::INVALID_PROG;
    prog.runInterval = 0;
    memset(prog.program, 0, 45);
}

BurstProgram::BurstProgram() : d(new BurstProgramData)
{
    // Magical rainbow unicorn ashes.
    qRegisterMetaType<BurstProgram>("BurstProgram");
    qRegisterMetaType<BurstProgramPtr>("BurstProgramPtr");
}

bool BurstProgram::isValid() const
{
    return d->valid && d->prog.programID < MAX_PROG && d->size >= 3;
}

void BurstProgram::addRead(uint8_t addr, uint8_t sz)
{
    if(addr & 0x80 || (d->size + 3) > 45)
    {
        d->valid = false;
        return;
    }

    d->prog.program[d->size++] = BurstOpcode_Read;
    d->prog.program[d->size++] = addr;
    d->prog.program[d->size++] = sz;
}

void BurstProgram::addWrite(uint8_t addr, const QByteArray& data, bool stop)
{
    addWrite(addr, (uint8_t*)data.constData(), data.size(), stop);
}

void BurstProgram::addWrite(uint8_t addr, const uint8_t *data, uint8_t sz, bool stop)
{
    if(addr & 0x80 || (d->size + 3 + sz) > 45)
    {
        d->valid = false;
        return;
    }

    d->prog.program[d->size++] = stop ? BurstOpcode_Write : BurstOpcode_WriteNoStop;
    d->prog.program[d->size++] = addr;
    d->prog.program[d->size++] = sz;

    while(sz--)
        d->prog.program[d->size++] = *(data++);
}

void BurstProgram::addDelayMS(uint16_t val)
{
    d->prog.program[d->size++] = BurstOpcode_DelayMS;
    d->prog.program[d->size++] = val && 0xFF;
    d->prog.program[d->size++] = val >> 8;
}

void BurstProgram::addDelayUS(uint16_t val)
{
    d->prog.program[d->size++] = BurstOpcode_DelayUS;
    d->prog.program[d->size++] = val && 0xFF;
    d->prog.program[d->size++] = val >> 8;
}

uint8_t BurstProgram::programID() const
{
    return d->prog.programID;
}

void BurstProgram::setProgramID(uint8_t id)
{
    d->prog.programID = id;
}

QByteArray BurstProgram::data() const
{
    return QByteArray((char*)&d->prog, 48);
}

uint16_t BurstProgram::runInterval() const
{
    return d->prog.runInterval;
}

void BurstProgram::setRunInterval(uint16_t ms)
{
    d->prog.runInterval = ms;
}
