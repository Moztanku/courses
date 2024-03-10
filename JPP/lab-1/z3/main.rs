mod iter;
use iter::lib;

fn main() {
    let a = 10;
    let b = 15;
    let c = 5;

    let result = lib::solve(a, b, c);

    println!("x = {}, y = {}", result.x, result.y);
}