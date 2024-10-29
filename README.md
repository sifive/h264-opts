# h264-opts
The project includes RISC-V Vector optimizations for the H.264 decoder, implementing
- Motion compensation
- Intra prediction
- IDCT
- In-loop filtering
- Weighted prediction

 ## Build Instructions
 ```
CC=riscv64-unknown-linux-gnu-clang CFLAGS="-O3 -mcpu=TARGET_ARCH" make
```
