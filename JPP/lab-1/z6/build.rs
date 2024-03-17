extern crate cc;

fn main() {
    cc::Build::new()
        .include("src")
        .file("src/recu.c")
        .compile("library.a");
}