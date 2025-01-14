## Testing

### Running tests

To run the tests, you need to compile with the flag `BUILD_TESTS` enabled (`-DBUILD_TESTS:BOOL=ON`).
This will build all tests within the `tests` directory and generate a `tests` folder in the build directory, which contains the test executable.

Once the executable is generated, you can run the tests with the following command:
```bash
cd build/{build_type}/tests/unit
./crystalserver_ut

cd build/{build_type}/tests/integration
./crystalserver_it
```

#### Running tests with CTest

You can also run the tests using CTest:
```bash
-- from the build/{build_type} directory
-- to run all tests 
ctest --verbose

-- to run only unit tests
ctest --verbose -R unit

-- to run only integration tests
ctest --verbose -R integration
```

### Adding tests

Tests are added in the `tests` folder, in the root of the repository.
As much as possible, tests should be added in the same folder as the code they are testing:

```
- src
    - foo
        - foo.cpp
    - bar
        - bar.cpp
- tests
    - foo
        - foo_test.cpp
    - bar
        - bar_test.cpp
```

### Boost::ut

Tests are written using the Boost::ut framework.  We've chosen this framework because it is simple, macro-free, intuitive, and easy to use.
In this section, we will go over the basics of the framework, but you can find more information in the [Boost::ut documentation](https://boost-ext.github.io/ut/).
There are many ways to write tests, and we encourage you to read the documentation to find the way that works best for you.

#### Suites

Tests needs to be encapsulated by suites, which are defined using `suite<>` structure.
```cpp
suite<"foo"> test_foo = [] {
    // Tests go here
};
```

This puts all tests within test_foo under the suite "foo".
You can use declare multiple suites with the same name, and they will be merged together.
This allows you to declare suites in different files, and they will be merged together, keeping test files clean.

Avoid creating tests directly in the main function, as this will put them in the `global` suite, which is not recommended.

#### Tests

Tests can be defined using the `test()` lambda or the `_test` operator:
```cpp
suite<"foo"> test_foo = [] {
    "test 1"_test = [] {
        // Test 1
    };

    test("test 2") = [] {
        // Test 2
    };
};
```

#### Assertions

Both are equivalent, the received argument is the description of the test.
The description is used to identify the test in the output, and should be unique within a suite.

Assertions are done using the `expect()` function:
```cpp
suite<"foo"> test_foo = [] {
    "test 1"_test = [] {
        expect(eq(1_i, 1_i));
    };
};
```

It's always preferable to use comparison operators (eq, neq, etc.), as they provide better error messages.

#### Testing against injected dependencies

Testing against injected dependencies is done using the `di::extension::injector<>` class.
This class is used to create the dependency injection container, and can be used to set up the container for testing.
For example, to test the `RSA` class, we need to inject a `Logger` class, otherwise it will use the default SpdLog implementation.

```cpp
suite<"security"> rsaTest = [] {
	test("RSA::start logs error for missing .pem file") = [] {
		di::extension::injector<> injector{};
		DI::setTestContainer(&InMemoryLogger::install(injector));

		DI::create<RSA &>().start();

		auto &logger = dynamic_cast<InMemoryLogger &>(injector.create<Logger &>());

        expect(eq(1, logger.logs.size()) >> fatal);
		expect(
			eq(std::string{"error"}, logger.logs[0].level) and
			eq(std::string{"File key.pem not found or have problem on loading... Setting standard rsa key\n"}, logger.logs[0].message)
        );
	};
};
```
