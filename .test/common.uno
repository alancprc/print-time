Unison:SyntaxRevision1909.3;

__Flow sample_flow {
    OnStart = OnStart_sf;
    OnReset = evDefaultReset;
    __LoopNotify = __False;
}
__BinMap sample_binmap {
    __Bin Pass = 1;
    __Bin LoadComplete = 200;
    __Bin Fail = 201;
    __Bin evResetBin = 0;
    __Bin evDefaultBin = 0;
}
__Bin Pass {
    __Number = 1;
    __Result = __True;
    __CheckOverFlow = __True;
    __Color = 0;
}
__Bin LoadComplete {
    __Number = 200;
    __Result = __True;
    __CheckOverFlow = __True;
    __Color = 7;
}
__Bin Fail {
    __Number = 500;
    __Result = __False;
    __CheckOverFlow = __True;
    __Color = 2;
}
__Bin evDefaultBin {
    __Result = __False;
    __CheckOverFlow = __True;
    __Color = 2;
}
__Bin evResetBin {
    __Result = __False;
    __CheckOverFlow = __True;
    __Color = 2;
}

__PinType PinTypeNull {
    __Type = NullPin;
}
__AdapterBoard dummy_pkg {
    __Pin { __Name = dummy1; __XCoord = (0,0); __Shape = 0; __PinType = PinTypeNull; 
        __Connection[0] { }
    }
    __MaxSite = 4;
}
