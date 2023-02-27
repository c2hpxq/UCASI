# lock

## spinlock

### 硬件原子操作支持

底层的原子操作由`std::atomic_flag`提供。其成员函数：
- clear: atomically sets flag to false
- test_and_set: atomically sets the flag to true and obtains its previous value

test_and_set的实现会调用编译器的[builtin function](https://stackoverflow.com/questions/23930588/how-gcc-handles-built-in-function)：[__atomic_test_and_set](https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html)
```c++
_GLIBCXX_ALWAYS_INLINE bool
test_and_set(memory_order __m = memory_order_seq_cst) noexcept
{
    return __atomic_test_and_set (&_M_i, int(__m));
}

_GLIBCXX_ALWAYS_INLINE bool
test_and_set(memory_order __m = memory_order_seq_cst) volatile noexcept
{
    return __atomic_test_and_set (&_M_i, int(__m));
}
```

builtin function由编译器在编译期间处理，编译器决定如何为其生成代码。当然，对于编译器来说，builtin function只是一个符号，可以仅用于标记某些对象，检查其特定性质。

> Built-in Function: bool __atomic_test_and_set (void *ptr, int memorder)
> 
> This built-in function performs an atomic test-and-set operation on the byte at *ptr. The byte is set to some implementation defined nonzero “set” value and the return value is true if and only if the previous contents were “set”. It should be only used for operands of type bool or char. For other types only part of the value may be set.
> 
> All memory orders are valid.

> Built-in Function: void __atomic_clear (bool *ptr, int memorder)
> 
> This built-in function performs an atomic clear operation on *ptr. After the operation, *ptr contains 0. It should be only used for operands of type bool or char and in conjunction with __atomic_test_and_set. For other types it may only clear partially. If the type is not bool prefer using __atomic_store.
> 
> The valid memory order variants are __ATOMIC_RELAXED, __ATOMIC_SEQ_CST, and __ATOMIC_RELEASE.


我们可以翻阅编译器的处理过程来搜索它如何翻译这里的`__atomic_test_and_set`，但也可以通过反汇编来查看编译的结果：
```x86asm
0000000000401b60 <_ZN8SpinLock4lockEv>:

; ignore prologue

401bee:       b0 01                   mov    $0x1,%al
401bf0:       48 8b 4d d8             mov    -0x28(%rbp),%rcx
401bf4:       86 01                   xchg   %al,(%rcx)
401bf6:       88 45 cf                mov    %al,-0x31(%rbp)
401bf9:       8a 45 cf                mov    -0x31(%rbp),%al
401bfc:       3c 00                   cmp    $0x0,%al
401bfe:       0f 84 05 00 00 00       je     401c09 <_ZN8SpinLock4lockEv+0xa9>
401c04:       e9 67 ff ff ff          jmpq   401b70 <_ZN8SpinLock4lockEv+0x10>
401c09:       5d                      pop    %rbp
401c0a:       c3                      retq   
```
编译器内联了一条[xchg指令](https://c9x.me/x86/html/file_module_x86_id_328.html)
> If a memory operand is referenced, the processor's locking protocol is automatically implemented for the duration of the exchange operation, regardless of the presence or absence of the LOCK prefix or of the value of the IOPL.

大意是若该指令的一个操作数为内存地址，则会“锁定总线”使其独占内存访问权（这个理解需要修正细化）。

### C++ features
