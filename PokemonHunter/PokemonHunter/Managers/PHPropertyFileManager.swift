//
//  PHPropertyFileManager.swift
//  PokemonHunter
//
//  Created by Renaud Buisine on 08/09/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import Foundation

class PHPropertyFileManager {

    static func dictionary(From plistName:String) -> [String: Any]? {
        
        guard let path = Bundle(for: self).path(forResource: plistName, ofType: "plist") else {
            return nil
        }
        
        return NSDictionary(contentsOfFile: path) as? [String : Any]
    }
}
