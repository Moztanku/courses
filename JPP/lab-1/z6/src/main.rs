mod wrapper;

fn main() {
    unsafe {
        println!("factorial(5) = {}", wrapper::factorial(5));
        println!("gcd(15, 25) = {}", wrapper::gcd(15, 25));

        let pair = wrapper::solve(1, 2, 1);

        println!("solve(1, 2, 1) = ({}, {})", pair.x, pair.y);
    }
}