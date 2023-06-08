use base64::{encode, decode};
use std::io::{self, Write};

fn xor_with_key(input: &String, key: &String) -> String {
    let mut output = String::new();
    for (i, c) in input.chars().enumerate() {
        let key_char = key.chars().nth(i % key.len()).unwrap();
        let xored_char = (c as u8) ^ (key_char as u8);
        output.push(xored_char as char);
    }
    output
}

fn main() {
    //Declare `data` and `key`, `chs` for choose String
    let mut data = String::new();
    let mut key = String::new();
    let mut chs = String::new();
    
    println!("What yo want? [E]ncrypt OR [D]ecode");
    print!(">>> ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut chs).expect("Failed to read line");
    if chs.to_lowercase().chars().nth(0).unwrap() == 'e' {
        print!("data: ");
        io::stdout().flush().unwrap();
        io::stdin()
            .read_line(&mut data)
            .expect("Failed to read line");
        print!("key: ");
        io::stdout().flush().unwrap();
        io::stdin()
            .read_line(&mut key)
            .expect("Failed to read line");
        data = data.replace("\n", "");
        key = key.replace("\n", "");
        let xored = xor_with_key(&data, &key);
        let encoded = encode(xored);
        println!("{}", encoded);
    } else if chs.to_lowercase().chars().nth(0).unwrap() == 'd' {
        print!("data: ");
        io::stdout().flush().unwrap();
        io::stdin()
            .read_line(&mut data)
            .expect("Failed to read line");
        print!("key: ");
        io::stdout().flush().unwrap();
        io::stdin()
            .read_line(&mut key)
            .expect("Failed to read line");
        data = data.replace("\n", "");
        key = key.replace("\n", "");
        let decoded = String::from_utf8(decode(data).unwrap()).unwrap();
        let xored = xor_with_key(&decoded, &key);
        println!("{}", xored);
    }
}
