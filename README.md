# Welcome to the Inverted Index Project 👋

This C++ project implements an **Inverted Index** system, a fundamental data structure for building text search engines. It allows you to process documents (PDFs and simple text files), build an efficient index of the words contained within them, and then perform quick searches to find where these words or phrases appear.

## Features

* **Multi-Format Processing:** Supports reading and indexing documents in **PDF** format (using the Poppler library to internally convert them to TXT) and **TXT** files.
* **Text Normalization:** Performs text cleaning by converting all text to lowercase and filtering to keep only alphabetic characters, ensuring consistent searching regardless of capitalization. (The template mentioned accent removal, which is a common normalization step; the current code focuses on case and alphabetic filtering).
* **Efficient Indexing:** Utilizes a **Trie (Prefix Tree)** data structure to store words, enabling extremely fast lookups.
* **Precise Occurrence Location:** For each indexed word, the system stores an identifier (approximating the **page** or document segment) and the **line number** where the word was found.
* **Word and Phrase Search:** Capable of searching for individual words and checking for the presence of entire phrases within the index.

## How It Works

The project is divided into three main components that work together to create and manage the inverted index:

1.  ### `Documentos` (Reader and Pre-processor)

    This class serves as the interface for input files.

    * **PDF Reading:** If a PDF file is provided, the `Documentos` class uses the `poppler` library to extract text from each page. This extracted text is then saved into a temporary `.txt` file with the same base name for further processing.
    * **Text Pre-processing:** For all text files (original TXT or PDF converted to TXT), the `ProcessarTXT` method converts all text to lowercase and filters out non-alphabetic characters. The result is "clean" and standardized text, saved to `texto_processado.txt`, which is ideal for indexing.
    * **Reading and Indexing:** The `lerTXT` method then reads the cleaned text from `texto_processado.txt` line by line and word by word, sending each word to the `Trie` for indexing, along with its location (an identifier for page/document segment and line number).

2.  ### `Trie` (Prefix Tree)

    This is the central data structure for word storage.

    * A Trie is a tree where each node can represent a letter (though this implementation uses fixed-size arrays corresponding to 'a'-'z'). By traversing the nodes from the root, you form words.
    * **Insertion:** Each unique word from the document is inserted into the Trie. The path traversed in the tree forms the word, and at the final node of the word, a `ListaEncadeada` (Linked List) is attached to store occurrence details.
    * **Search:** The Trie allows for extremely fast searching of words and prefixes. By traversing the tree with the letters of the search query, the system can quickly determine if the word exists in the index.

3.  ### `ListaEncadeada` (Occurrences List)

    Associated with each word in the `Trie` is a `ListaEncadeada`. This list stores the occurrences of the word within the documents.

    * Each element in the `ListaEncadeada` (the `Chave` struct) represents a document segment or page (identified by a string, e.g., a page number).
    * Attached to each `Chave` is a sub-list (using the `Inf` struct) that contains the **line numbers** (as strings) where the word appears within that document/page.
    * This allows the system, when searching for a word, to return not just if it exists, but also its precise location(s) within the documents.

### Simplified Flow:

1.  **Input:** PDF or TXT file. The `main.cpp` currently uses a hardcoded path for a PDF.
2.  **`Documentos::lerPDF`:** If PDF, reads the file using Poppler, extracts text, and saves it to a `.txt` file.
3.  **`Documentos::lerTXT` calls `Documentos::ProcessarTXT`:** Cleans the text from the source `.txt` file (converts to lowercase, handles punctuation/non-alphabetic characters) and saves to `texto_processado.txt`.
4.  **`Documentos::lerTXT`:** Reads words from `texto_processado.txt`, identifying an approximate page/document ID and line number for each word.
5.  **`Trie::insere`:** Inserts each word into the Trie. At the end of each word's path, it attaches/updates a `ListaEncadeada`.
6.  **`ListaEncadeada::inserir`:** Stores the page/document ID and line information for each word occurrence.
7.  **Search (`main.cpp` options):** When searching for a word or phrase in the `Trie` (`trie.pesquisar` or `trie.palavra`), the system quickly retrieves the corresponding `ListaEncadeada`(s) and displays the locations.

-----

## Getting Started

To compile and run this project, you'll need a C++ compiler and the Poppler library. The project appears to be configured for Visual Studio using vcpkg for dependencies, as suggested by the log files.

Alternatively, for a manual build (e.g., with g++ on Linux):

* A C++ compiler (like g++).
* The **Poppler C++ Development library** (for PDF reading). On Debian/Ubuntu-based systems, you can install it using:
    ```bash
    sudo apt-get install libpoppler-cpp-dev
    ```
    For other operating systems or build systems like vcpkg, please refer to their respective Poppler installation instructions. The `vcpkg.applocal.log` indicates that DLLs such as `poppler.dll` and `poppler-cpp.dll` are being used.

### Compilation (Example with g++)

Navigate to the project's root directory in your terminal and compile the C++ source files:

```bash
g++ -o BuscaFinal main.cpp Leitor.cpp Trie.cpp Lista.cpp -I/path/to/poppler/include -L/path/to/poppler/lib -lpoppler-cpp -std=c++11
```

* `-o BuscaFinal`: Specifies the output executable name.
* `main.cpp Leitor.cpp Trie.cpp Lista.cpp`: Lists your `.cpp` source files.
* `-I/path/to/poppler/include -L/path/to/poppler/lib`: Adjust these paths to where your Poppler headers and libraries are installed.
* `-lpoppler-cpp`: Links with the Poppler C++ library.
* `-std=c++11`: Ensures compatibility with C++11 features (you can use `c++17` or newer if your code and Poppler version support it).

If using Visual Studio with vcpkg, these linkage details are typically handled by the project settings.

### Execution

After successful compilation:

Currently, the input file path is hardcoded in `main.cpp`:
`string caminhoDiretorio = "C:/Users/ryanp/Downloads/Pdfs/ts.pdf";`

You will need to either:
1.  Modify this path in `main.cpp` to point to your desired PDF or TXT file before compiling.
2.  Change the code to accept the file path as a command-line argument.

Once set up, run the executable:
```bash
./BuscaFinal 
# or, on Windows, if compiled with MSVC:
# BuscaFinal.exe
```

The program will process the specified file, build the index, and then present a menu to perform searches.

-----

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).

**Copyright (c) 2025 Ryan Pablo Coelho Luiz**

For more details on the terms of use, please refer to the `LICENSE` file if you choose to include one in the root of this repository.

-----

## Author

This project was conceived and developed by:

**MonkeyShock**
GitHub: (https://github.com/MonkeyShock)
```
