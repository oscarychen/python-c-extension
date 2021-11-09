# If you did not install the module, you can still import it if the module is
# in the same directory as this file (copying the module from build/ folder).
import MyModule

print(MyModule.version())
print(MyModule.fib(10))

try:
    MyModule.raise_exception()
except Exception as e:
    print(e)

print(MyModule.return_none())
print(MyModule.return_none_2())
