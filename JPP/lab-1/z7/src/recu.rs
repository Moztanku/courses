pub mod lib {
    pub struct Pair {
        pub x: i32,
        pub y: i32,
    }

    pub fn factorial(n: i32) -> i32 {
        if n < 2 {
            return 1;
        } else {
            return n * factorial(n - 1);
        }
    }

    fn gcdr(a: i32, b: i32) -> i32 {
        if a == 0 {
            return b;
        } else {
            return gcdr(b % a, a);
        }
    }

    pub fn gcd(mut a: i32, mut b: i32) -> i32 {
        if a < b {
            std::mem::swap(&mut a, &mut b);
        }

        return gcdr(a, b);
    }

    pub fn solve(a: i32, b: i32, c: i32) -> Pair {
        let mut result = Pair {x: 0, y: 0};

        let d = gcd(a, b);

        if c % d == 0 {
            result = egcd(a, b);
            result.x *= c / d;
            result.y *= c / d;
        }

        return result;
    }

    fn egcd(a: i32, b: i32) -> Pair {
        let mut result = Pair {x: 1, y: 0};

        if b != 0 {
            result = egcd(b, a % b);
            let temp = result.x;

            result.x = result.y;
            result.y = temp - (a / b) * result.y;
        }

        return result;
    }
}