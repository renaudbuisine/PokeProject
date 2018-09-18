//
//  PHControl.swift
//  PokemonHunter
//
//  Created by Renaud Buisine on 08/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import UIKit

protocol PHControl {
    var frame: CGRect { get set }
    
    func touchDown(atPoint pos: CGPoint)
    func touchMoved(toPoint pos: CGPoint)
    func touchUp(atPoint pos: CGPoint)
}
