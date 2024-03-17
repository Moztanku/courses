extern crate libc;

#[repr(C)]
pub struct Pair {
    pub x: libc::c_int,
    pub y: libc::c_int,
}

extern {
    pub fn factorial(n: libc::c_int) -> libc::c_int;
    pub fn gcd(a: libc::c_int, b: libc::c_int) -> libc::c_int;
    pub fn solve(a: libc::c_int, b: libc::c_int, c: libc::c_int) -> Pair;
}