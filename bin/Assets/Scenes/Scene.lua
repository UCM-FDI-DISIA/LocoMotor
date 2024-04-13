Scene = {
    
    -- CAMERA --
    MainCamera = {
        Camera = {
            background = "0.9 0.7 0.5"
        },
        AudioListener = {},
        Transform = {
            position = "0 500 450",
            size = "1 1 1",
            rotation = "-50 0 0"
        },
    },

    -- UI --
    Cross_01 = {
        UIImage = {
            anchor = "0.5 0.5",
            position = "-80 100",
            pivot = "0.5 0.5",
            size = "70 70",
            image = "CrossMaterial"
        }
    },
    Cross_02 = {
        UIImage = {
            anchor = "0.5 0.5",
            position = "0 100",
            pivot = "0.5 0.5",
            size = "70 70",
            image = "CrossMaterial"
        }
    },
    Cross_03 = {
        UIImage = {
            anchor = "0.5 0.5",
            position = "80 100",
            pivot = "0.5 0.5",
            size = "70 70",
            image = "CrossMaterial"
        }
    },
    ScoreBackground = {
        UIImage = {
            anchor = "0.5 0.5",
            position = "0 100",
            pivot = "0.5 0.5",
            size = "375 150",
            image = "UIMaterial"
        }
    },
    UICountdown = {
        UIText = {
            anchor = "1 0",
            position = "-10 10",
            pivot = "1 0",
            size = "20 25",
            text = "hola ijos de puta, les mando un saludo desde lua",
            font = "Heavitas",
            alignment = "r",
            colorTop = "0.9 0 0.2",
            colorBot = "0.2 0 0.9"
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
            Play = ""
        }
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
    Objectytdyuyfdyry = {
        AudioSource = {
            Volume = 1,
            PlayOnAwake = "Assets/Sounds/prueba.wav"
        }
    }
}