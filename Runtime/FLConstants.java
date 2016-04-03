
/**
 * SER 502 Project 2 Group 31.
 * 
 * Flash Programming Language
 * 
 * Flash Keywords for Operations
 */
public enum FLConstants {
	PUSH, ASSIGN, END, ARGS,
	EQUAL, NOT_EQUAL, GREATER, GREATER_THAN_EQUAL, LESSER, LESSER_THAN_EQUAL,
	CONDITION_FALSE_JUMP_TO,CONDITION_TRUE_JUMP_TO,
	ADD, SUB, MULTIPLY, DIVIDE, MODULUS,
	QUIT,PRINT,END_FUNCTION,FUNCTION,CALL_FUNCTION, RETURN;
	
	public static boolean contains(String test) {
	    for (FLConstants e : FLConstants.values()) {
	        if (e.name().toLowerCase().equals(test)) {
	            return true;
	        }
	    }
	    return false;
	}
}
