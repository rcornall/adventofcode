use std::{fs::File, io::BufRead, io::BufReader, io::Error, io::ErrorKind, path::Path};

pub fn get_file_into_vec(path: impl AsRef<Path>) -> Result<Vec<u32>, std::io::Error> {
    // include_str! would do..
    let f = File::open(path).expect("Unable to open file");

    BufReader::new(f)
        .lines()
        .map(|l| {
            l.and_then(|n| {
                n.parse()
                    // need to pass thru io::Error type for BufReader.lines() result<string, (io)error> type.. weird.
                    .map_err(|e| Error::new(ErrorKind::InvalidData, e))
            })
        })
        .collect()
}
