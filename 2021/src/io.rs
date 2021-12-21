use std::io::Read;

pub fn get_file_as_string(name: &str) -> String {
    let mut f = std::fs::File::open(format!("data/{}.txt", name)).expect("Unable to open file");
    let mut contents = String::new();
    f.read_to_string(&mut contents).expect("Unable to read file to string");

    contents
}
