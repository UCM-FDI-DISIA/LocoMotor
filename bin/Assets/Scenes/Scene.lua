Scene = {
    
    -- CAMERA --
    MainCamera = {
        Camera = {},
        AudioListener = {},
        Transform = {
            position = "0 500 450",
            size = "1 1 1",
            rotation = "-50 0 0"
        },
    },

    -- CHARACTERS --
    cube = {
        Transform = {
            position = "0 0 0",
            size = "20 20 20",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "CubemanMesh.mesh",
            material = "CustomMaterial"
        },
        PlayerController = {
        },
        ParticleSystem = {
            Particle = "GunShot",
            PlayOnStart = ""
        },
        ParticleSystem = {
            Particle = "Smoke",
            PlayOnStart = ""
        }
    },
    Player_2 = {
        Transform = {
            position = "0 0 0",
            size = "20 20 20",
            rotation = "0 -40 0"
        },
        MeshRenderer = {
            mesh = "ConemanMesh.mesh",
            material = "RedCharacter"
        },
        PlayerController = {
        }
    },
    Player_3 = {
        Transform = {
            position = "0 0 0",
            size = "20 20 20",
            rotation = "0 -40 0"
        },
        MeshRenderer = {
            mesh = "SpheremanMesh.mesh",
            material = "GreenCharacter"
        },
        PlayerController = {
        }
    },
    Player_4 = {
        Transform = {
            position = "0 0 0",
            size = "20 20 20",
            rotation = "0 -40 0"
        },
        MeshRenderer = {
            mesh = "CylindermanMesh.mesh",
            material = "PurpleCharacter"
        },
        PlayerController = {
        }
    },

    GameplayManager = {
        Transform = {
            position = "0 0 0",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        GameplayManager = {
        }
    },
    LocalMultiplayerManager = {
        Transform = {
            position = "0 0 0",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        LocalMultiplayerManager = {
        }
    },

    -- GUNS
    revolver = {
        Transform = {
            position = "-140 0 0",
            size = "15 15 15",
            rotation = "115 -130 0"
        },
        MeshRenderer = {
            mesh = "Revolver.mesh",
            material = "Revolver"
        }
    },
    Bullet = {
        Transform = {
            position = "0 0 0",
            size = "20 20 20",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "Bullet.mesh",
            material = "Bullet"
        },
        Bullet = { }
    },

    -- PLATFORMS --
    platform_01 = {
        Transform = {
            position = "0 0 0",
            size = "130 130 130",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "Platform_01.mesh",
            material = "Platform"
        }
    },
    platform_02_left = {
        Transform = {
            position = "-160 80 -160",
            size = "130 130 130",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "Platform_02.mesh",
            material = "Platform"
        }
    },
    platform_02_right = {
        Transform = {
            position = "160 80 -160",
            size = "130 130 130",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "Platform_02.mesh",
            material = "Platform"
        }
    },
    platform_03_left = {
        Transform = {
            position = "-160 40 40",
            size = "130 130 130",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "Platform_03.mesh",
            material = "Platform"
        }
    },
    platform_03_right = {
        Transform = {
            position = "160 40 40",
            size = "-130 130 130",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "Platform_03.mesh",
            material = "Platform"
        }
    },
    platform_04 = {
        Transform = {
            position = "0 60 -180",
            size = "-130 130 130",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "Platform_04.mesh",
            material = "Platform"
        }
    },
    backPlane = {
        Transform = {
            position = "0 -140 -100",
            size = "700 700 700",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "BackPlane.mesh",
            material = "BackPlane"
        }
    },

    -- SOUNDS --
    Object = {
        AudioSource = {
            Volume = 1,
            PlayOnAwake = "Assets/Sounds/prueba.wav"
        }
    },
    Emitter = {
        EventEmitter = {
            EventID = "event:/Music/Level 02",
            Play = "";
        }
    },
}