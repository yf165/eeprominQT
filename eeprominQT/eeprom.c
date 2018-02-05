


    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <linux/i2c.h>
    #include <linux/i2c-dev.h>

    #include "eeprom.h"

    int openEep(const char* device)
    {
        int fd =open(device, O_RDWR);
        if (fd< 0) {
               perror("open");
        }
        return fd;
    }

    int readEep(int fd,int devAddr,int regAddr,int num,char* readBuf)
    {
        int i = 0,j = 0;
        char c = 0;
        int ret = -1;
        struct i2c_msg  msg;
        struct i2c_at24_r rd = {0};
        struct i2c_rdwr_ioctl_data ioctl_data;
        struct i2c_msg msgs;

        ioctl_data.nmsgs= 1;
        ioctl_data.msgs= &msgs;

        // 写入要读的地址
        msgs.addr  = devAddr;
        msgs.flags = 0;
        rd.addr = regAddr;
        msgs.len   = sizeof(rd.addr);
        msgs.buf   = (unsigned char*)&rd.addr;
        usleep(INTERVALOFBLOCKWR);
        ret = ioctl(fd, I2C_RDWR, &ioctl_data);
    //	printf("ioctl write start register address fot read 0x%x, return :%d\n",regAddr,ret );
        if(ret < 0 ){
            perror("ioctl");
            return -1;
        }
        usleep(INTERVALOFBLOCKWR);
        // 连续读取num个byte
        msgs.addr   = devAddr;
        msgs.flags |= I2C_M_RD;
    //    msgs.len    = sizeof(rd.rdata);
        msgs.len = num;
        msgs.buf    = (unsigned char*)&rd.rdata[0];
        ret = ioctl(fd, I2C_RDWR, &ioctl_data);
        if(ret < 0 ){
            perror("ioctl");
            return -1;
        }
    //    printf("ioctl read, return :%d\n", ioctl(fd, I2C_RDWR, &ioctl_data));
 //       memccpy(readBuf,ioctl_data.msgs->buf,num);
        for(i = 0;i <num;i++){
            readBuf[i] = *(ioctl_data.msgs->buf+i);
        }

        return 0;
    }
    int printBuf(const char *buf,int regAddr,int num)
    {
        int i = 0,j = 0;
        char c = 0;
        printf("    ");
        for ( i = 0; i < 16;i++) {
            printf("%2x ",i);
        }
        printf("\n");
        for ( i = 0; i < num/16;i++) {
            printf("%2x: ",i+regAddr/16);
            for (j = 0;j<16; j++){
                printf("%2x ",*(buf+i*16+j));
            }
            printf(" ");
            for (j = 0;j<16; j++){
                c = *(buf+i*16+j);
                if((c == 0xd) || (c == 0xa))
                {
                    printf(" ");
                }else{
                    printf("%c ",c);
                }
            }
            printf("\n");
        }
        printf("\n");
        return 0;
    }
    int writeEep(int fd,int devAddr,int regAddr,const unsigned char *writeContent, int num)
    {
        int i = 0,j = 0;
        int cnt =0;
        int ret = -1;
        struct i2c_msg  msg;
        struct i2c_at24_w wd = {0};
        struct i2c_rdwr_ioctl_data ioctl_data;
        struct i2c_msg msgs;

        // 要写入的消息
        ioctl_data.nmsgs= 1;
        ioctl_data.msgs= &msgs;

        i = 0;
        usleep(INTERVALOFBLOCKWR);
        do{
            if(i==(num+MAXWRITENUMONCE-1)/MAXWRITENUMONCE-1){
                cnt = num - i*4;
            }else{
                cnt = MAXWRITENUMONCE;
            }
            for ( j = 0; j < cnt;j++) {
                wd.wdata[j] = *(writeContent+i*MAXWRITENUMONCE+j);
            }
            wd.addr    = regAddr+i*MAXWRITENUMONCE;
            msgs.addr  = 0x50;
            msgs.flags = 0;
            msgs.len   = sizeof(wd.addr)+cnt;
            msgs.buf   = (unsigned char*)&wd;
            ret = ioctl(fd, I2C_RDWR, &ioctl_data);
            if(ret < 0){
                perror("ioctl");
                return -1;
            }
    //		printf("ioctl write addr %x, return :%d\n",wd.addr ,ioctl(fd, I2C_RDWR, &ioctl_data));
            usleep(INTERVALOFBLOCKWR);
            i++;
        }while(i<(num+MAXWRITENUMONCE-1)/MAXWRITENUMONCE);

    }
    int closeEep(int fd)
    {
        close(fd);
    }

