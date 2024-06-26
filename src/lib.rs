extern "C" {
  fn hello();
}

#[no_mangle]
fn test() {
  println!("Hello from Rust");
  unsafe {
    hello();
  }
}

