#ifndef CORE_SETTINGS
    #define CORE_SETTINGS

    #define STACK_INITSIZE 32
    
    enum INSTRUCTIONS{
        STACK_PUSH =         0x10,// spush <value>
        STACK_POP =          0x11,// spop  <address>
        STACK_CLEAR =        0x12,// sclear
        STACK_CALL =         0x1F,// scall <interrupt>
        STACK_JUMP_IF_ZERO = 0x20,// sjz   <address>
    };
    enum STACK_CALLS{
        SC_STACK_EXIT =      0x0F, // exit    <code from stack>
        SC_STACK_PUTCHAR =   0x10  // putchar <char from stack>
    };
#endif