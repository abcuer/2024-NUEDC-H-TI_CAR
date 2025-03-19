#include "MYIIC.h"

uint8_t i2c0_write_n_byte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *buf, uint8_t nBytes)
{
    static uint8_t temp_reg_dddr=0;
    uint8_t n;
    uint32_t Byte4Fill;
    temp_reg_dddr = RegAddr;
    DL_I2C_fillControllerTXFIFO(I2C_1_INST, &buf[0], nBytes);

    /* Wait for I2C to be Idle */
    while (!(DL_I2C_getControllerStatus(I2C_1_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_flushControllerTXFIFO(I2C_1_INST); 
    DL_I2C_fillControllerTXFIFO(I2C_1_INST, &temp_reg_dddr, 1);
    /* Send the packet to the controller.
     * This function will send Start + Stop automatically.
     */
    DL_I2C_startControllerTransfer(I2C_1_INST, DevAddr,
    DL_I2C_CONTROLLER_DIRECTION_TX, (nBytes+1));
    n = 0;
    do {
        Byte4Fill = DL_I2C_getControllerTXFIFOCounter(I2C_1_INST);
        if(Byte4Fill > 1)
        {
            DL_I2C_fillControllerTXFIFO(I2C_1_INST, &buf[n], 1);
            n++;
        }
        }
    while(n<nBytes);

    /* Poll until the Controller writes all bytes */
    while (DL_I2C_getControllerStatus(I2C_1_INST) &DL_I2C_CONTROLLER_STATUS_BUSY_BUS);

    /* Trap if there was an error */
    if (DL_I2C_getControllerStatus(I2C_1_INST) &DL_I2C_CONTROLLER_STATUS_ERROR){
        /* LED will remain high if there is an error */
        __BKPT(0);
    }
    /* Add delay between transfers */
    

    return nBytes;
}


