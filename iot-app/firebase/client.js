import { initializeApp } from 'firebase/app'
import { getDatabase, ref, update } from 'firebase/database'

const firebaseConfig = {
  apiKey: 'AIzaSyAmutmzCYjlxjrQtIVydSU5EYUgRfofFiI',
  authDomain: 'esp32-controller-dd8ce.firebaseapp.com',
  databaseURL: 'https://esp32-controller-dd8ce-default-rtdb.firebaseio.com',
  projectId: 'esp32-controller-dd8ce',
  storageBucket: 'esp32-controller-dd8ce.appspot.com',
  messagingSenderId: '9513004910',
  appId: '1:9513004910:web:d2a7f8b407ff6ab7e15b7f',
  measurementId: 'G-2G92BC8K68'
}

const app = initializeApp(firebaseConfig)

export const db = getDatabase(app)

export const updateValue = (path, value) => {
  const data = {
    state: value
  }
  const updates = {}
  updates[path] = data

  update(ref(db), updates)
}
