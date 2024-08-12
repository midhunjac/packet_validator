# PACKET VALIDATOR
A CLI to validate custom packets according to a set of rules.

## Usage

Clone the repo and navigate into the cloned repo.

```sh
git clone https://github.com/midhunjac/packet_validator.git
cd packet_validator
```

Compile the program using

```sh
gcc -o main main.c
```

After building, run the application

```sh
./main
```
![image](https://github.com/user-attachments/assets/0906c129-118e-4649-803f-3a325bf46e58)

## Result

Upon successfully running the main application, the application iterates through all elements of array packets in packets.h and checks if they are valid. A snapshot of the console output is shown below. The output can be directed to a log file as well. This is /output.txt

![image](https://github.com/user-attachments/assets/d79aa6a2-351a-4773-8539-47d4a0cb3a52)


## Testing

The repo includes a unit testing application test.c to test the CLI. The testing application includes a set of valid and invalid packets and the expected response from the main application. The testing application invokes the main application and checks the response from the main application against the expected response. In case these do not match, an assert is triggered.
To compile the testing application, use

```sh
gcc -o test test.c
```

After successful build, run the test

```sh
./test
```
If everything works as expected, the result is printed to the console as shown below

![image](https://github.com/user-attachments/assets/d13480d1-2596-4828-80ca-8da6dafe3368)

New test cases can be easily added to the testing application with minimal changes
