
/// run part1, pass in input.
pub fn part1(depths: &Vec<u32>) -> u32 {
    // parse_input(input);
    let mut ret: u32 = 0;

    let mut last_depth: u32 = 0;
    for depth in depths {
        if last_depth != 0 && depth > &last_depth {
            ret += 1;
        }
        last_depth = depth.clone();
    }

    ret
}

/// run part2, pass input.
pub fn part2(depths: &Vec<u32>) -> u32 {
    let mut ret = 0;

    let mut window1: [&u32; 3] = [&depths[0], &depths[1], &depths[2]];
    let mut window2: [&u32; 3] = [&depths[1], &depths[2], &depths[3]];

    let prev: u32 = window1.iter().copied().sum(); // avoids clone. although rust optimizer looks like clone will copy anyways.
    let curr: u32 = window2.iter().copied().sum();

    if curr > prev {
        ret += 1;
    }

    let mut i = 3;
    for depth in depths.iter().skip(4) {
        window1[i % 3] = window2[(i - 1) % 3];
        window2[i % 3] = depth;

        let prev: u32 = window1.iter().copied().sum();
        let curr: u32 = window2.iter().copied().sum();

        if curr > prev {
            ret += 1;
        }

        i += 1;
    }

    ret
}
