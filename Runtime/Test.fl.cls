push b
push 6
assign
function recur t
push 1
push t
not_equal
jump_false 20
push t
print
push t
push t
push 1
sub
assign
call_function recur t
push t
print
end_function
call_function recur b
halt