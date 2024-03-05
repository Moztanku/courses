mod lib
{
    pub
    fn factorial(n: i32) -> i32
    {
        let mut result: i32 = 1;

        for i in 1..n { result *= i; }

        return result;
    }

    pub
    fn gcd(mut a: i32, mut b: i32) -> i32
    {
        if a < b {
            std::mem::swap(&mut a, &mut b);
        }

        while b != 0 {
            a = a % b;
            std::mem::swap(&mut a, &mut b);
        }

        return a;
    }

    pub
    struct Pair {
        pub x: i32,
        pub y: i32
    }

    pub
    fn solve(a: i32, b: i32, c: i32) -> Pair
    {
        let mut result = Pair{x: 0, y: 0};

        let d: i32 = gcd(a, b);

        if c % d == 0 {
            result = egcd(a, b);
            result.x = result.x * (c / d);
            result.y = result.y * (c / d);
        }

        return result;
    }

    fn egcd(a: i32, b: i32) -> Pair
    {
        let mut result = Pair{x: 0, y: 0};

        if b == 0 {
            result.x = 1;
        } else {
            result = egcd(b, a % b);
            std::mem::swap(&mut result.x, &mut result.y);
            result.y = result.y - (a / b) * result.x;
        }

        return result;
    }
}

// use std::fmt;

fn main()
{
    println!("{} {}", lib::factorial(6), lib::gcd(5,4));
    
    let a = 70;
    let b = 145;
    let c = 35;
    let result: lib::Pair = lib::solve(a, b, c);

    println!(
        "({} x {}) + ({} x {}) = {}",
        a, result.x,
        b, result.y,
        c
    );

    return;
}