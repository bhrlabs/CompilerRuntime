
/**
 * SER 502 Project 2 Group 31.
 * 
 * Flash Programming Language
 * 
 * Flash Keywords for Operations
 */
public enum FLConstants {
	PUSH, HALT, ARGS, DATA, IN_INT, LD_INT, LD_VAR, STORE, GOTO, OUT_INT, IN_BOL, LD_BOL, OUT_BOL,
	IN_STR, LD_STR, OUT_STR, DEF,
	GT, EQ, GTEQ, LT, LTEQ,
	JMP_FALSE,CONDITION_TRUE_JUMP_TO,
	ADD, SUB, MULT, DIVIDE, PWR,
	FUN_END, FUN_INIT, CALL, POP,
	ADDSTK, REMSTK;
	
	public static boolean contains(String test) {
	    for (FLConstants e : FLConstants.values()) {
	        if (e.name().toLowerCase().equals(test)) {
	            return true;
	        }
	    }
	    return false;
	}
}
