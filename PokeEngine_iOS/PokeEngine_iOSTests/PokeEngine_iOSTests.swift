//
//  PokeEngine_iOSTests.swift
//  PokeEngine_iOSTests
//
//  Created by Renaud Buisine on 22/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

import XCTest
@testable import PokeEngine_iOS

class PokeEngine_iOSTests: XCTestCase {
    
    private var game: PokeGame_iOS!
    private var gameDelegate: MockPokeGameDelegate!
    
    override func setUp() {
        super.setUp()
        
        XCTContext.runActivity(named: "GIVEN a PokeGame iOS and its delegate object") { _ in
            gameDelegate = MockPokeGameDelegate()
            
            game = PokeGame_iOS(name: "TestGame")
            game.delegate = gameDelegate
        }
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testLifeCycle() {
        
        XCTContext.runActivity(named: "WHEN Running game") { _ in
            gameDelegate.addUpdateExpectations(5)
            gameDelegate.addFixedUpdateExpectations(3)
            game.run()
        }
        
        XCTContext.runActivity(named: "THEN update is called with timestamp AND fixed update is called") { _ in
            wait(for: gameDelegate.expectations, timeout: 2000)
            XCTAssert(gameDelegate.didUpdateCalled)
            XCTAssert(gameDelegate.didFixedUpdateCalled)
        }
        
        
        XCTContext.runActivity(named: "WHEN setting pause") { _ in
            game.pause()
            sleep(1) // to be sure current update is not running
            gameDelegate.reset()
            sleep(1)
        }
        
        XCTContext.runActivity(named: "THEN no update callback functions are called") { _ in
            XCTAssertFalse(gameDelegate.didUpdateCalled)
            XCTAssertFalse(gameDelegate.didFixedUpdateCalled)
        }
        
        
        XCTContext.runActivity(named: "WHEN resuming") { _ in
            gameDelegate.reset()
            gameDelegate.addUpdateExpectations(5)
            gameDelegate.addFixedUpdateExpectations(3)
            game.resume()
        }
        
        XCTContext.runActivity(named: "THEN update callback functions are called and normal running behavior is back") { _ in
            wait(for: gameDelegate.expectations, timeout: 2000)
            XCTAssert(gameDelegate.didUpdateCalled)
            XCTAssert(gameDelegate.didFixedUpdateCalled)
        }
        
        
        XCTContext.runActivity(named: "WHEN stopping") { _ in
            game.stop()
            sleep(1) // to be sure current update is not running
            gameDelegate.reset()
            sleep(1)
        }
        
        XCTContext.runActivity(named: "THEN no update callback functions are called") { _ in
            XCTAssertFalse(gameDelegate.didUpdateCalled)
            XCTAssertFalse(gameDelegate.didFixedUpdateCalled)
        }
    }
    
}
