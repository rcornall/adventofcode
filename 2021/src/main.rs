mod day01;
mod io;

fn main() {
    let lines = io::get_file_into_vec("data/day01.txt");

    let v = match lines {
        Ok(val) => val,
        Err(_) => panic!("avoiding the use of unwrap for no reason"),
    };

    let one = day01::part1(&v);
    println!("one: {}", one);

    let two = day01::part2(&v);
    println!("two: {}", two);
}
