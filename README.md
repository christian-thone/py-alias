# PyAlias - Command Line Tool

## Description

PyAlias is a C++ script that allows you to set variable aliases, because who likes naming readable variables in python.  Especially long variables like `randomly_generated_number`.  It's so much faster to write `rnum`... right?? I might just be the only one.

## How to Compile

<details>

<summary>View Text</summary>

### Instructions

You will need a C++ compiler, such as `g++`. [[*download*]](https://github.com/msys2/msys2-installer/releases/download/2022-01-28/msys2-x86_64-20220128.exe)

Once installed, run `g++` you'll get a fatal error about having no files with the command.  That means it's installed properly.

Now to compile the actual script you're here for.  Simple.

Use the command: `g++ ./src/main.cpp -o pyalias`

Now there should be an executable file in your directory.

</details>

## How to add to PATH

<details>

<summary>View Text</summary>

### Instructions

Move the executable into another directory in which you won't have to move it ever again.  I suggest putting it into a folder in Documents.  Now copy the path to the directory.

To add this to PATH (windows). Follow these steps:

Open your windows search menu and type "Enviroment"

You should see the following:

https://prnt.sc/26um25p

Open that menu.

You should see the following:

https://prnt.sc/26um4ga

Now click the button that states: "Enviroment Variables..."

A new menu should pop up, this may look scary, don't worry! It's pretty simple, look around until you find the word "Path" **(MAKE SURE IT IS IN THE USER VARIABLES SECTION!!!)**, highlight it by clicking on it once.

Now click "Edit..."

Again another menu will pop up!

On the side of the menu is a list of buttons, press New

I have mine saved to a secondary storage drive.  There now once you close out of all of those menus you should be able to run the script from anywhere within your terminal.

</details>

## Usage

<details>

<summary>View Text</summary>

### Instructions

Okay so now I assume you followed all previous steps (Compiling and adding to path)

Now what's next? Well now you learn how to use it.

Somewhere in your directory you'll need a file named `config.alias`

Now that you have this file, the syntax is:

```alias
variable alias
```

In which each key:pair set are on individual lines.

Variable = The variable you want to change
Alias = What you wanna change that variable to.

For example look at this:

```alias
rnum randomly_generated_number
string1 user_name
```

The key is `rnum` and the value is `randomly_generated_number` so this means any word that is `rnum` will be changed to `randomly_generated_number`.  Simple right?

Yes it is.  That's why I made it like that.

Now that you have your config file, you're pretty much done.

Now for actually running the script.

In your command line type

`pyalias [path_to_input_file] [path_to_output_file] [path_to_config_file]`

Example:
`pyalias ./tests/main.py ./tests/alias.py ./tests/config.alias `

As you can see here `main.py` is the input file, `alias.py` is the output file and `config.alias` is the config file.

Press Enter and you should see the output file have all the original code, just with your aliases in place of the actual variables.

</details>