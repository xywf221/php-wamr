export fn add(a: i64,b: i64) i64{
    return a+b;
}

export fn fib(x: i64) i64 {
    if (x <= 1) return x;
    return fib(x - 1) + fib(x - 2);
}

//zig build-lib math.zig -target wasm32-freestanding -dynamic -rdynamic
