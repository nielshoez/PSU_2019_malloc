## PSU_2019_malloc

Recode the standard LIBC function malloc realloc calloc free realloc_array in c using a best fit algorithm

## How to use

``` make```
This will compile a shared library called ```libmy_malloc.so```.

You can try to launch different programs by using the 
```LD_PRELOAD=$(pwd)/libmy_malloc.so program_name``` command.

Example :
```LD_PRELOAD=$(pwd)/libmy_malloc.so ls -l``` will launch the ls program with -l flag.

![alt text](https://i.imgur.com/4T3mEJe.png)
## Running the tests

```make tests_run```

## Authors

* **Niels Hoez** - [nielshoez](https://github.com/nielshoez)


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details


