in_int b
function testfirst c r
ld_var c
out_int 0
ld_var r
out_int 0
end_function
function testsecond c
ld_var c
ld_int 2
mult
store d
ld_var d
out_int 0
end_function
ld_int 5
store t
call_function testfirst t b
call_function testsecond b
halt