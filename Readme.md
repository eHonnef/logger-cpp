# Logger

Simple logger class that uses std::format library.

This logger uses the new [C++20 std::format](https://en.cppreference.com/w/cpp/utility/format/format).

## Usage

- Include the folder `code/include` in your project and include the header `Logger/Logger.hpp`
- Set the Log level by simply defining: `using Logger = eho::CLogger<eho::LogLevel::Warning>`.
- Then simply use as `Logger::Error("the message with {} formatting", "some")`.
  - You can enable/disable a specific log by using as `Logger::Error<false>("the message with {} formatting", "some")`. As default the template parameter is true.

Available levels:

- Trace
- Debug
- Info
- Warning
- Error
- Fatal

Check the [main.cpp](code/src/main.cpp) file for more usage example.

### Changing the formatting

You need to provide a class with the following function signature:

```c++
template<LogLevel t_eLogLevel, typename... Args>
void Print(std::string_view strMessage, const std::source_location location, const Args &...args) {
    // Do your formatting + output here
}
```

This function will be called for the output and also, format the string inside that function, just change it as it suits you (file output, terminal output, etc).

Then update the line as follows: `using Logger = eho::CLogger<eho::LogLevel::Warning, MyCustomFormatter>`.

# TODO

- Logging server
- Log to a file

# License

Under Mozilla Public License, v. 2.0. Check [License file](LICENSE).
