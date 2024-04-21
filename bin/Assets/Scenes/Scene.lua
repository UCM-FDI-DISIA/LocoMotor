Scene = {
    
    -- CAMERA --
    MainCamera = {
        Camera = {
            background = "0.9 0.7 0.5"
        },
        AudioListener = {},
        Transform = {
            position = "0 50 45",
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
            position = "0 300", -- 100
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
            rotation = "0.1",
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
            size = "2 2 2",
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
        },
        RigidBody = {
            mass = 1,
            size = "4 4 4"
        },
    },
    Player_2 = {
        Transform = {
            position = "0 0 0",
            size = "2 2 2",
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
            size = "2 2 2",
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
            size = "2 2 2",
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
            position = "-10 10 0",
            size = "1.5 1.5 1.5",
            rotation = "115 -130 0"
        },
        MeshRenderer = {
            mesh = "Revolver.mesh",
            material = "Revolver"
        },
        Weapon = {
        }
    },
    Bullet = {
        Transform = {
            position = "0 0 0",
            size = "2 2 2",
            rotation = "0 0 0"
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
            size = "13 13 13",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "Platform_01.mesh",
            material = "Platform"
        }
    },
    platform_02_left = {
        Transform = {
            position = "-16 8 -16",
            size = "13 13 13",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "Platform_02.mesh",
            material = "Platform"
        }
    },
    platform_02_right = {
        Transform = {
            position = "16 8 -16",
            size = "13 13 13",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "Platform_02.mesh",
            material = "Platform"
        }
    },
    platform_03_left = {
        Transform = {
            position = "-16 4 4",
            size = "13 13 13",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "Platform_03.mesh",
            material = "Platform"
        }
    },
    platform_03_right = {
        Transform = {
            position = "16 4 4",
            size = "-13 13 13",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "Platform_03.mesh",
            material = "Platform"
        }
    },
    platform_04 = {
        Transform = {
            position = "0 6 -18",
            size = "-13 13 13",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "Platform_04.mesh",
            material = "Platform"
        }
    },
    backPlane = {
        Transform = {
            position = "0 -14 -10",
            size = "70 70 70",
            rotation = "0 0 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "BackPlane.mesh",
            material = "BackPlane"
        }
    },


    -- COLLISION --
    platform_01_collision = {
        Transform = {
            position = "0 -3 0",
            size = "25 5 25",
            rotation = "0 0 0"
        },
        -- MeshRenderer = {
        --     mesh = "DebugCube.mesh",
        --     material = "DebugCube"
        -- },
        RigidBody = { mass = 0 },
    },
    platform_02_left_collision = {
        Transform = {
            position = "-16 -2 -16",
            size = "8 10 8",
            rotation = "0 0 0"
        },
        -- MeshRenderer = {
        --     mesh = "DebugCube.mesh",
        --     material = "DebugCube"
        -- },
        RigidBody = { mass = 0 },
    },
    platform_02_right_collision = {
        Transform = {
            position = "16 -2 -16",
            size = "8 10 8",
            rotation = "0 0 0"
        },
        -- MeshRenderer = {
        --     mesh = "DebugCube.mesh",
        --     material = "DebugCube"
        -- },
        RigidBody = { mass = 0 },
    },
    platform_03_left_collision = {
        Transform = {
            position = "-19 0 8",
            size = "5 5 16",
            rotation = "0 0 0"
        },
        -- MeshRenderer = {
        --     mesh = "DebugCube.mesh",
        --     material = "DebugCube"
        -- },
        RigidBody = { mass = 0 },
    },
    platform_03_right_collision = {
        Transform = {
            position = "19 0 8",
            size = "5 5 16",
            rotation = "0 0 0"
        },
        -- MeshRenderer = {
        --     mesh = "DebugCube.mesh",
        --     material = "DebugCube"
        -- },
        RigidBody = { mass = 0 },
    },
    platform_03_left_2_collision = {
        Transform = {
            position = "-11 0 19",
            size = "3 5 5",
            rotation = "0 0 0"
        },
        -- MeshRenderer = {
        --     mesh = "DebugCube.mesh",
        --     material = "DebugCube"
        -- },
        RigidBody = { mass = 0 },
    },
    platform_03_right_2_collision = {
        Transform = {
            position = "11 0 19",
            size = "3 5 5",
            rotation = "0 0 0"
        },
        -- MeshRenderer = {
        --     mesh = "DebugCube.mesh",
        --     material = "DebugCube"
        -- },
        RigidBody = { mass = 0 },
    },
    platform_04_collision = {
        Transform = {
            position = "0 7 -16",
            size = "8 1 5",
            rotation = "0 0 0"
        },
        -- MeshRenderer = {
        --     mesh = "DebugCube.mesh",
        --     material = "DebugCube"
        -- },
        RigidBody = { mass = 0 },
    },





    Objectytdyuyfdyry = {
        AudioSource = {
            Volume = 1,
            PlayOnAwake = "Assets/Sounds/prueba.wav"
        }
    }
}