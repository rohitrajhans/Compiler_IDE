package main

import (
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"os"
	"os/exec"
	"net/http"
	"github.com/gorilla/mux"
	"encoding/json"
)

type CodeStruct struct {
	Code string `json:"code"`
	Input string `json:"input"`
}

func createCompilerBinaries() {
	// creates the executable files for the compiler
	cmd := exec.Command("make")
	cmd.Dir = "./compiler"
	err := cmd.Run()
	if err != nil {
		log.Fatalf("cmd.Run() failed with %s\n", err)
	}
}

func execCompiler(code string, input string) string {

	// fmt.Println(code)
	// fmt.Println(input)

	// write code to testcase.txt
	file_c, err := os.Create("compiler/testcase.txt")
	if err != nil {
		fmt.Println(err)
	} else {
		file_c.WriteString(code)
	}
	file_c.Close()

	// write input to input.txt
	file_i, err := os.Create("compiler/input.txt")
	if err != nil {
		fmt.Println(err)
	} else {
		file_i.WriteString(input)
	}
	file_i.Close()
	
	// fmt.Println("Written to files")
	
	outfile, _ := os.Create("./compiler/output.txt")
	outfile.Sync()
	defer outfile.Close()

	// compile the code and check for errors
	cmd := exec.Command("./compiler", "testcase.txt", "code.asm")
	cmd.Stdout = outfile
	cmd.Stderr = os.Stderr
	cmd.Dir = "./compiler"
	err = cmd.Run()
	if err != nil {
		log.Fatalf("cmd.Run() failed with %s\n", err)
	}

	outfile.Close()

	output, err := ioutil.ReadFile("./compiler/output.txt")
	if err != nil {
		log.Fatal(err)
	}

	// check compiled output for errors
	// Success is stored in case on no error
	if string(output) == "Success" {
		fmt.Println("Code compilation successful")
	} else {
		// in case of errors return the error stream stored in output.txt
		// fmt.Println(string(output))
		return string(output)
	}

	// creates the executable file from asm code
	cmd = exec.Command("make", "executable")
	cmd.Dir = "./compiler"
	err = cmd.Run()
	if err != nil {
		log.Fatalf("cmd.Run() failed with %s\n", err)
	}

	outfile, _ = os.Create("./compiler/output.txt")
	outfile.Sync()
	defer outfile.Close()
	
	bytes, err := ioutil.ReadFile("./compiler/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	// get input for executable from input.txt
	cmd = exec.Command("./exe", "< input.txt")
	stdin, err := cmd.StdinPipe()
	if err != nil {
		log.Fatal(err)
	}
	cmd.Stdout = outfile
	cmd.Stderr = os.Stderr
	cmd.Dir = "./compiler"
	err = cmd.Start()
	if err != nil {
		log.Fatalf("cmd.Start() failed with %s\n", err)
	}
	_, err = io.WriteString(stdin, string(bytes))
	stdin.Close()
	if err != nil {
		log.Fatal(err)
	}
	
	cmd.Wait()

	// store output in output.txt and return that output as a string
	output, err = ioutil.ReadFile("./compiler/output.txt")
	if err != nil {
		log.Fatal(err)
	}
	
	return string(output)
}

// function to create new router
func newRouter() *mux.Router {
	r := mux.NewRouter()
	r.HandleFunc("/", serveFiles).Methods("GET")
	r.HandleFunc("/compile", handleCompiler).Methods("POST")
	r.HandleFunc("/getCode", getData).Methods("POST")

	// set static directory
	staticFileDirectory := http.Dir("./static/")
	staticFileHandler := http.StripPrefix("/static/", http.FileServer(staticFileDirectory))
	r.PathPrefix("/static/").Handler(staticFileHandler).Methods("GET")
	return r
}

// handler to serve files
func serveFiles(w http.ResponseWriter, r *http.Request) {
	fmt.Println(r.URL.Path, r.Method)

	path := "./static" + r.URL.Path

	if r.URL.Path == "/" {
		path = path + "index.html"
	}

	http.ServeFile(w, r, path)	
}

// handler to execute the compiler code
func handleCompiler(w http.ResponseWriter, r *http.Request) {
	
	// parse data
	err := r.ParseForm()

	// In case of any error, report
	if err != nil {
		fmt.Println(fmt.Errorf("Error: %v", err))
		w.WriteHeader(http.StatusInternalServerError)
		return
	}

	// read code and input
	code := r.Form.Get("code")
	input := r.Form.Get("input_values")

	// get the output
	output := execCompiler(code, input)
	// fmt.Println(output)

	// return output as json
	w.Header().Set("Content-Type", "application/json; charset=UTF-8")
	w.WriteHeader(http.StatusOK)
	if err := json.NewEncoder(w).Encode(output); err != nil {
		panic(err)
	}
}

func getData(w http.ResponseWriter, r *http.Request) {

	err := r.ParseForm()

	// In case of any error, report
	if err != nil {
		fmt.Println(fmt.Errorf("Error: %v", err))
		w.WriteHeader(http.StatusInternalServerError)
		return
	}

	id := r.Form.Get("id")
	// fmt.Println(id)
	
	flag := 0
	code_path := "./compiler/sample_code/c" + id + ".txt"
	input_path := "./compiler/sample_code/i" + id + ".txt"

	code, err := ioutil.ReadFile(code_path)
	if err != nil {
		flag = 1
	}

	input, err := ioutil.ReadFile(input_path)
	if err != nil {
		flag = 1
	}

	if flag == 1 {
		w.WriteHeader(http.StatusInternalServerError)
	    w.Write([]byte("500 - Something bad happened!"))
	}

	resp, err := json.Marshal(CodeStruct{Code: string(code), Input: string(input)})

	if err != nil {
		log.Fatal(err)
	}


	w.Header().Set("Content-Type", "application/json; charset=UTF-8")
	w.WriteHeader(http.StatusOK)
	fmt.Fprint(w, string(resp))
}

func getPort() string {
	p := os.Getenv("PORT")
	if p != "" {
	  return ":" + p
	}
	return ":3000"
}

func main() {

	fmt.Println("Creating compiler Binaries")
	// createCompilerBinaries()

	// create new router to handle requests
	fmt.Println("Creating router")
	r := newRouter()
	fmt.Println("Getting Port")
	port := getPort()
	fmt.Printf("Listening on %s\n", port)
	log.Fatal(http.ListenAndServe(port, r))
}
