push b
push 6
assign
function testfirst c
push c
print
end_function
function testsecond c
push d
push c
push 2
add
assign
push d
print
end_function
call_function testfirst b
end