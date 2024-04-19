## 说明
1. 目的：生成一个适配`正点原子APOLLO(STM32H743II)开发板通过FMC扩展的NandFlash`的下载算法文件`FLM`；
2. 本工程通过`D:\keil5_ARM\Packs\Keil\STM32H7xx_DFP\3.1.1\CMSIS\Flash\STM32H750_FMC`例程修改而来；
3. 当前状态：擦除和编程外部`NandFlash`返回的状态都是正常的，但是实际的数据不对；
4. 通过调试判断，上面的问题不是由于地址错误引起的。
5. 由于加载`FLM`对外部`Flash`进行烧录之后，之前的数据还在，所以实际上擦除过程就没成功。
6. 若`Init()`返回`1`，则通过这个`FLM`文件进行烧录时会提示擦除错误；
7. 在`NAND_INit()`后加上`HAL_NAND_Reset()`后报验证失败错误（不加时验证通过）；说明在擦除以及下载时，`Init_fmc()`运行成功，在`Verify()`时，`Init_fmc()`运行失败（由`HAL_NAND_Reset()`引起的？）。