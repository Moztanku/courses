#!(crate_type = "staticlib")

mod recu; use recu::lib;

#[repr(C)]
pub struct Pair {
    pub x: i32,
    pub y: i32,
}

#[no_mangle]
pub extern fn rust_factorial(n: i32) -> i32 {
    lib::factorial(n)
}

#[no_mangle]
pub extern fn rust_gcd(a: i32, b: i32) -> i32 {
    lib::gcd(a, b)
}

#[no_mangle]
pub extern fn rust_solve(a: i32, b: i32, c: i32) -> Pair {
    let result: lib::Pair = lib::solve(a, b, c);
    Pair {x: result.x, y: result.y}
}