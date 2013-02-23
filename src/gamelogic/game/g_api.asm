code

equ memset                                -1
equ memcpy                                -2
equ memcmp                                -3
equ strncpy                               -4
equ sin                                   -5
equ cos                                   -6
equ asin                                  -7
equ tanf                                  -8
equ atanf                                 -9
equ atan2                                 -10
equ sqrt                                  -11
equ floor                                 -12
equ ceil                                  -13
equ trap_SyscallABIVersion                -256
equ trap_Print                            -257
equ trap_Error                            -258
equ trap_Milliseconds                     -259
equ trap_Cvar_Register                    -260
equ trap_Cvar_Update                      -261
equ trap_Cvar_Set                         -262
equ trap_Cvar_VariableIntegerValue        -263
equ trap_Cvar_VariableStringBuffer        -264
equ trap_Cvar_LatchedVariableStringBuffer -265
equ trap_Argc                             -266
equ trap_Argv                             -267
equ trap_SendConsoleCommand               -268
equ trap_FS_FOpenFile                     -269
equ trap_FS_Read                          -270
equ trap_FS_Write                         -271
equ trap_FS_Rename                        -272
equ trap_FS_FCloseFile                    -273
equ trap_FS_GetFileList                   -274
equ trap_LocateGameData                   -275
equ trap_DropClient                       -276
equ trap_SendServerCommand                -277
equ trap_LinkEntity                       -278
equ trap_UnlinkEntity                     -279
equ trap_EntitiesInBox                    -280
equ trap_EntityContact                    -281
equ trap_EntityContactCapsule             -282
equ trap_Trace                            -283
equ trap_TraceNoEnts                      -283
equ trap_TraceCapsule                     -284
equ trap_TraceCapsuleNoEnts               -284
equ trap_PointContents                    -285
equ trap_SetBrushModel                    -286
equ trap_InPVS                            -287
equ trap_InPVSIgnorePortals               -288
equ trap_SetConfigstring                  -289
equ trap_GetConfigstring                  -290
equ trap_SetConfigstringRestrictions      -291
equ trap_SetUserinfo                      -292
equ trap_GetUserinfo                      -293
equ trap_GetServerinfo                    -294
equ trap_AdjustAreaPortalState            -295
equ trap_AreasConnected                   -296
equ trap_BotAllocateClient                -297
equ trap_BotFreeClient                    -298
equ trap_GetUsercmd                       -299
equ trap_GetEntityToken                   -300
equ trap_RealTime                         -301
equ trap_SnapVector                       -302
equ trap_SendGameStat                     -303
equ trap_AddCommand                       -304
equ trap_RemoveCommand                    -305
equ trap_GetTag                           -306
equ trap_LoadTag                          -307
equ trap_RegisterSound                    -308
equ trap_GetSoundLength                   -309
equ trap_Parse_AddGlobalDefine            -310
equ trap_Parse_LoadSource                 -311
equ trap_Parse_FreeSource                 -312
equ trap_Parse_ReadToken                  -313
equ trap_Parse_SourceFileAndLine          -314
equ trap_BotGetServerCommand              -315
equ trap_AddPhysicsEntity                 -316
equ trap_AddPhysicsStatic                 -317
equ trap_SendMessage                      -318
equ trap_MessageStatus                    -319
equ trap_RSA_GenerateMessage              -320
equ trap_QuoteString                      -321
equ trap_GenFingerprint                   -322
equ trap_GetPlayerPubkey                  -323
equ trap_GetTimeString                    -324
equ trap_BotSetupNav                      -325
equ trap_BotShutdownNav                   -326
equ trap_BotSetNavMesh                    -327
equ trap_BotFindRoute                     -328
equ trap_BotUpdatePath                    -329
equ trap_BotNavTrace                      -330
equ trap_BotFindRandomPoint               -331
equ trap_BotEnableArea                    -332
equ trap_BotDisableArea                   -333
equ trap_BotAddObstacle                   -334
equ trap_BotRemoveObstacle                -335
equ trap_BotUpdateObstacles               -336
