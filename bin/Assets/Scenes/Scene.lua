Scene = {
    MainCamera = {
        Camera = {},
        AudioListener = {},
        Transform = {
            position = "0 200 250",
            size = "1 1 1",
            rotation = "-45 0 0"
        },
    },
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
    -- cubePrueba = {
    --     Transform = {
    --         position = "0 0 0",
    --         size = "20 20 20",
    --         rotation = "0 0 0"
    --     },
    --     MeshRenderer = {
    --         mesh = "CubemanMesh.mesh",
    --         material = "CustomMaterial"
    --     },
    --     PlayerController = {
    --     },
    --     ParticleSystem = {
    --         Particle = "Smoke",
    --         PlayOnStart = ""
    --     }
    -- },
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
    LocalMultiplayerManager = {
        Transform = {
            position = "0 0 0",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        LocalMultiplayerManager = {
        }
    },
        -- cube = {
    --     Transform = {
    --         position = "0 0 -150",
    --         size = "20 20 20",
    --         rotation = "15 -40 0"
    --     },
    --     MeshRenderer = {
    --         mesh = "ConemanMesh.mesh",
    --         material = "RedCharacter"
    --     }
    -- },
    -- cube = {
    --     Transform = {
    --         position = "0 0 -150",
    --         size = "20 20 20",
    --         rotation = "15 -40 0"
    --     },
    --     MeshRenderer = {
    --         mesh = "SpheremanMesh.mesh",
    --         material = "GreenCharacter"
    --     }
    -- },
    -- cube = {
    --     Transform = {
    --         position = "0 0 -150",
    --         size = "20 20 20",
    --         rotation = "15 -40 0"
    --     },
    --     MeshRenderer = {
    --         mesh = "CylindermanMesh.mesh",
    --         material = "PurpleCharacter"
    --     },
    --     ParticleSystem = {
    --         Particle = "Smoke",
    --         PlayOnStart = ""
    --     }
    -- },
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
    platform = {
        Transform = {
            position = "0 -38 0",
            size = "130 130 130",
            rotation = "0 -10 0" -- "0 -40 0" 
        },
        MeshRenderer = {
            mesh = "Platform_01.mesh",
            material = "Platform"
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
    }
}