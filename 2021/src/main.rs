mod io;
mod day01;


fn main() {
    println!("Hello, world!");
    let input = day01::get_input();
    let one = day01::part1(&input);
    println!("one: {}", one);

    // let two = day01::part2();
    // println!("two: {}", two);
}
