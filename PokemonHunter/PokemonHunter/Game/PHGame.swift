//
//  PHGame.swift
//  PokemonHunter
//
//  Created by Renaud Buisine on 08/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import PokeEngine_iOS

class PHGame: NSObject {

    private let game: PokeGame
    
    init(with name: String) {
        game = PokeGame.init(name: name)
        super.init()
        
        game.delegate = self
    }
}

extension PHGame: PokeGameDelegate {
    func game(_ game: PokeGame, didAdd scene: PokeScene) {
        guard let associatedScene = self.sceneFrom(scene) else {
            return
        }
        associatedScene.delegate = self
    }
}
