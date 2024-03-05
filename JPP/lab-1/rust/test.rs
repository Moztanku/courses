mod iter
{
    pub
    fn factorial(n: i32) -> i32
    {
        let mut result: i32 = 1;

        for i in 1..n { result *= i; }

        return result * n;
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

    fn egcd(mut a: i32, mut b: i32) -> Pair
    {
        let mut result = Pair{x: 1, y: 0};
        let mut prev = Pair{x: 0, y: 1};
        
        while b != 0 {
            let q = a / b;

            let mut temp = result;
            temp.x -= q * prev.x;
            temp.y -= q * prev.y;

            result = prev;
            prev = temp;

            let temp = a;
            a = b;
            b = temp - q * b;
        }

        return result;
    }
}

mod recu
{
    pub
    fn factorial(n: i32) -> i32
    {
        return if n < 2 { 1 } else { n * factorial(n - 1) };
    }

    pub
    fn gcd(a: i32, b: i32) -> i32
    {
        return if b == 0 { a } else { gcd(b, a % b) };
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
        return if b == 0 {
            Pair{x: 1, y: 0}
        } else {
            let result = egcd(b, a % b);
            Pair{x: result.y, y: result.x - (a / b) * result.y}
        };
    }
}

// use std::fmt;

fn main()
{
    println!("{} {}", iter::factorial(6), iter::gcd(5,4));
    println!("{} {}", recu::factorial(6), recu::gcd(5,4));
    
    let a = 70;
    let b = 145;
    let c = 35;
    let result: iter::Pair = iter::solve(a, b, c);

    println!(
        "({} x {}) + ({} x {}) = {} == {}",
        a, result.x,
        b, result.y,
        a * result.x + b * result.y,
        c
    );

    let result: recu::Pair = recu::solve(a, b, c);
    println!(
        "({} x {}) + ({} x {}) = {} == {}",
        a, result.x,
        b, result.y,
        a * result.x + b * result.y,
        c
    );

    return;
}