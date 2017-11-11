# TinyTrayIndicator
A tiny command line tool to show an indicator icon in the notification area.

# Usage
> TinyTrayIndicator.exe
Creates a new instance with the `TinyTrayIndicator` class name.

> TinyTrayIndicator.exe custom_class_name
Creates a new instance with the `custom_class_name` class name.

> TinyTrayIndicator.exe custom_class_name 123
Creates a new instance with the `custom_class_name` class name and icon id `123`.
If an instance with the `custom_class_name` class name already exists, changes its icon id `123`.

> TinyTrayIndicator.exe custom_class_name close
Closes the instance with the `custom_class_name` class name.

# Adding new icons
You can use a resource editor such as Resource Hacker to add new icons. `123` in the example above is the icon resource id.

# Using with [`winapiexec`](http://rammichael.com/winapiexec)
> winapiexec.exe u@SendMessageW ( u@FindWindowW TinyTrayIndicator 0 ) 0x8000 101 0

`TinyTrayIndicator` is the class name. You can launch TinyTrayIndicator with one parameter to use a custom class name. For example:
