in_int b
function testfirst c r
push c
print
push r
print
end_function
function testsecond c
push d
push c
ld_int 2
multiply
assign
push d
print
end_function
push t
ld_int 5
assign
call_function testfirst t b
halt