extern "C" {
  fn hello();
}

fn main() {}

#[no_mangle]
fn test() {
  unsafe {
    hello();
  }
}

