# TinyTrayIndicator
Set a tray icon by sending a message.

# Using with `winapiexec`
> winapiexec.exe u@SendMessageW ( u@FindWindowW TinyTrayIndicator 0 ) 0x8000 101 0

`TinyTrayIndicator` is the class name. You can launch TinyTrayIndicator with one parameter to use a custom class name. For example:

> TinyTrayIndicator.exe MyCustomClassName

You can use a resource editor such as Resource Hacker to add new icons. `101` in the example above is the icon resource id.
