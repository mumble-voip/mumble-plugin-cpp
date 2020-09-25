# mumble-plugin-cpp

A C++ wrapper for around the C plugin interface that was introduced with Mumble 1.4.0

## What is it?

The aim of this wrapper is to provide an interface that feels "native" when using C++. Therefore it hides away the fact that the plugin
API is actually a bunch of free C-functions by providing a C++ class `MumblePlugin` that can be used to implement the needed functionality using
member functions.

On top of that some housekeeping has been automated within this class. For instance plugins implemented using this wrapper don't have to care about
how to obtain the API functions used to interact with Mumble.

Speaking of API functions: There is also a C++ wrapper around the Mumble API functions (which originally are just a bunch of function pointers). This
wrapper has the following features:
- No need to pass the plugin's ID as a parameter for every API function call
- No way to forget to check important error codes (the wrapper will **throw exceptions** of type `MumbleAPIException` if there is an error)
- No need to worry about which returned values need to be freed after usage (smart-pointer-like `MumbleResourceWrapper` takes care of that)
- No "out-params": All returned values are actual return values


## How do I use it?

When using the wrapper all you have to do in order to create a plugin is to create a class that extends from `MumblePlugin`. You can then overwrite
any of the virtual functions in order to hook into the respective callbacks. The API can be accessed via the `m_api` member variable.

Furthermore you have to implement `MumblePlugin::getPlugin` to return a reference to a static instance of your plugin class (which thereby effectively
becomes a singleton):

```
MumblePlugin &MumblePlugin::getPlugin() noexcept {
    static MyPluginClass plugin;

    return plugin;
}
```

By default only a small subset of functionality is available for you to implement. If you want to implement any of the missing functions,
you can set the following cmake-variables:
- `positional-audio`
- `server-event-callbacks`
- `audio-callbacks`
- `plugin-data-callbacks`
- `key-event-callbacks`
- `plugin-update`

Additionally you can also use these meta-variables: `all-callbacks`, `all-features`

Due to technical reasons it is (at the moment) impossible to simply use `target_link_libraries` to link to the
wrapper. Instead one has to use a cmake-generator expression to include the respective files:
```
add_library(example SHARED
	# Add the object files from the wrapper-lib
	$<TARGET_OBJECTS:mumble_plugin_cpp_wrapper>
	...
)
```

followed by adapting the needed compile-definitions and include-directories:
```
get_target_property(NEEDED_COMPILE_DEFINITONS mumble_plugin_cpp_wrapper INTERFACE_COMPILE_DEFINITIONS)
target_compile_definitions(example
	PUBLIC
		${NEEDED_COMPILE_DEFINITONS}
)
get_target_property(NEEDED_INCLUDE_DIRS mumble_plugin_cpp_wrapper INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(example
	PUBLIC
		${NEEDED_INCLUDE_DIRS}
)
```

You can have a look at the [example plugin](examplePlugin/) in order to check out a basic example that should get
you started writing your own plugins.


## Requirements

In order to use the wrapper, you need to have
- A compiler that is iso-C++17 conform
- cmake v3.0 or newer

Other than that there are no further dependencies of the wrapper.

