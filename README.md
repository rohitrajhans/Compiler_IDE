# Compiler for A Toy Language with an Online IDE

- Compiler built as part of the term project for the course **CS F363 - Compiler Construction**. 
Original Github Repo to view development of compiler: [https://github.com/Saujas/Compiler-Project-CS-F363](https://github.com/Saujas/Compiler-Project-CS-F363)
- Play around with the language at: bits-compiler.herokuapp.com
- View language specifications here: [https://github.com/rohitrajhans/Compiler_IDE/blob/master/compiler/Language%20specifications.pdf](https://github.com/rohitrajhans/Compiler_IDE/blob/master/compiler/Language%20specifications.pdf)

## How to run
1. Make sure the binaries for the compiler exist. If not, run `make -C compiler` from the root directory
2. Run `go run main.go` to start the server
3. Visit `localhost:3000` to open the Web App 

## Technology Stack
- Client-side: JavaScript, JQuery
- Server-side: Go
- Compiler for Toy Language: C

For more details on the compiler implementation check [this](https://github.com/Saujas/Compiler-Project-CS-F363) out

## Details on deployment
Deplyoment is not straightforward since gcc libraries are not installed by default on the Heroku cloud host. Follow the steps listed [here]([https://leanpub.com/howtodeployagowebapptoheroku101/read](https://leanpub.com/howtodeployagowebapptoheroku101/read)) to deploy the Go app. To add the runtime gcc environment, I followed these steps

1. Add two additional buildpacks: For [C](https://github.com/heroku/heroku-buildpack-c.git) and to install other [apt-dependencies]([https://elements.heroku.com/buildpacks/heroku/heroku-buildpack-apt](https://elements.heroku.com/buildpacks/heroku/heroku-buildpack-apt)).
2. The buildpack for C requires a Makefile in the root directory of the project. Build the compiler binaries when building the app. Add `make -C compiler` to the Makefile in the root directory to create compiler binaries while building the app.
3.  Create an Aptfile in the root folder to install the apt-dependencies. Add the following dependencies to the Aptfile. These will be installed while building the app.
	- build-essential
	-	nasm
	- gcc-multilib
	- libtool
	- glibc-source
	- libc-bin
	- libc-dev-bin
	- libc6
	- libc6-dev
4. Add `--sysroot=/app/.apt` after each gcc call to use the newly installed dependencies.