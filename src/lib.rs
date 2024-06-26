extern "C" {
  fn hello();
}

#[no_mangle]
fn test() {
  println!("[test] Hello from Rust");
  unsafe {
    hello();
  }
}

