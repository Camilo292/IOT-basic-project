import styles from '../../styles/switch.module.css'
import { useEffect, useState } from 'react'
import { db, updateValue } from '../../firebase/client'
import { ref, onValue } from 'firebase/database'

export default function Switch (props) {
  const starCountRef = ref(db, props.path + '/state')
  useEffect(() => {
    onValue(starCountRef, (snapshot) => {
      const data = snapshot.val()
      setChecked(data)
    })
  })
  const [checked, setChecked] = useState(false)

  const handleChange = () => {
    updateValue(props.path, !checked)
  }

  return (
    <>
      <label className = {styles.switch}>
        <input type ='checkbox'
          checked = {checked}
          onChange = {handleChange}
        />
        <span className = {styles.slider} />
      </label>
    </>
  )
}
