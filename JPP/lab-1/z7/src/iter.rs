pub mod lib {
    pub struct Pair {
        pub x: i32,
        pub y: i32,
    }

    pub fn factorial(n: i32) -> i32 {
        let mut result = 1;
        for i in 1 .. n+1 {
            result *= i;
        }

        return result;
    }

    pub fn gcd(mut a: i32, mut b: i32) -> i32 {

        if a < b {
            std::mem::swap(&mut a, &mut b);
        }

        while b != 0 {
            a = a % b;
            std::mem::swap(&mut a, &mut b);
        }

        return a;
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

    fn egcd(mut a: i32, mut b: i32)  -> Pair {
        let mut result = Pair {x: 1, y: 0};
        let mut prev = Pair {x: 0, y: 1};

        while b != 0 {
            let q = a / b;

            let temp = Pair {x: result.x, y: result.y};
            result.x = prev.x;
            result.y = prev.y;

            prev.x = temp.x - q * prev.x;
            prev.y = temp.y - q * prev.y;

            let temp = a;
            a = b;
            b = temp % b;
        }

        return result;
    }
}