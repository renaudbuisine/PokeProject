//
//  PHMapResourceContainer.swift
//  PokemonHunter
//
//  Created by Renaud Buisine on 09/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

//MARK: - Protocol

protocol PHMapResourceContainer: PHResourceContainer {

}

//MARK: - Default class

class PHDefaultMapResourceContainer {
    
}

extension PHDefaultMapResourceContainer :PHMapResourceContainer {
    func load(_ completion: @escaping PHResourceContainerLoadCompletionBlock) {
        completion()
    }
}
